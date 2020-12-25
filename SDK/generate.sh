#!/bin/bash -e

#REV="2018.3326"
REV="2100.9999"

BETA=0

while test $# -gt 0; do
        case "$1" in
                -h|--help)
                        echo "generate.sh - generates iOS plugins for Appodeal"
                        echo " "
                        echo "./generate.sh [--beta|-b]"
                        echo " "
                        echo "options:"
                        echo "-h, --help        show brief help"
                        echo "-b, --beta        uses plugin.beta for output"
                        exit 0
                        ;;
                -b|--beta)
                        BETA=1
                        shift
                        ;;
                *)
                        break
                        ;;
        esac
done

if [ $BETA == 1 ]; then
    PLUGINS=plugins.beta
else
    PLUGINS=plugins
fi


pushd "$(dirname "$0")" > /dev/null
ROOT=$(pwd)
popd > /dev/null

function stripBitcode {
    local DEST_BIN="$1"
    mv "$DEST_BIN" "$DEST_BIN.tmp"
    $(xcrun -f bitcode_strip) "$DEST_BIN.tmp" -r -o "$DEST_BIN"
    rm "$DEST_BIN.tmp"

    mv "$DEST_BIN" "$DEST_BIN.tmp"
    $(xcrun -f bitcode_strip) "$DEST_BIN.tmp" -r -o "$DEST_BIN"
    rm "$DEST_BIN.tmp"
}

function extactArc {
    local src="$1"
    local lib="$2"
    local dstDir="$3"
    local archs="$4"
    
    mkdir -p "$dstDir"
    rm -f "$dstDir/*.a"

    local arcOuts=()
    local liposWasOK=1
    for arch in $archs; do
        out="$dstDir/${lib%.a}.$arch.a"
        if lipo "$src" -thin "$arch" -output "$out"; then
            arcOuts+=("$out")
        else
            liposWasOK=0
        fi
    done

    if [ $liposWasOK -eq 1 ]; then
        lipo -create "${arcOuts[@]}" -output "$dstDir/$lib"
        stripBitcode "$dstDir/$lib"
    fi
    rm -f "${arcOuts[@]}"
}

function extractArchitecturesLib {
    local src="$1"
    local lib="$2"
    local dstDir="$3"

    extactArc "$src" "$lib" "$dstDir/iphone"      "armv7 arm64"
    extactArc "$src" "$lib" "$dstDir/iphone-sim"  "i386 x86_64"
}

function extractArchitecturesFramework {
    local src="$1"
    local dstDir="$2"

    local lib
    lib=$(basename "${1%.framework}")
    src="$src/$lib"

    extactArc "$src" "$lib" "$dstDir/iphone/$(basename "$1")"      "armv7 arm64"
    extactArc "$src" "$lib" "$dstDir/iphone-sim/$(basename "$1")"  "i386 x86_64"
}

function makeMetadata {
    local dstDir="$1"

    for device in "iphone" "iphone-sim"
    do
        [ -d "$dstDir/$device" ] || continue
        if [ ! -e "$dstDir/$device/metadata.lua" ]
        then
            cp ios_metadata_template.lua "$dstDir/$device/metadata.lua"
        fi

        local metadataLibs=""
        for l in "$dstDir/$device/"*.a
        do
            [ -e "$l" ] || continue
            local bn
            bn=$(basename "$l")
            bn=${bn#lib}
            bn=${bn%.a}
            metadataLibs+=" '$bn',"
        done

        local metadataFrameworks=""
        for l in "$dstDir/$device/"*.framework
        do
            [ -e "$l" ] || continue
            local bn
            bn=$(basename "$l")
            bn=${bn%.framework}
            metadataFrameworks+=" '$bn',"
        done
        for l in "$dstDir/$device/resources/Frameworks/"*.framework
        do
            [ -e "$l" ] || continue
            local bn
            bn=$(basename "$l")
            bn=${bn%.framework}
            metadataFrameworks+=" '$bn',"
        done

        sed "s#frameworks = {.*}#frameworks = {$metadataFrameworks }#" "$dstDir/$device/metadata.lua" | sed "s#staticLibs = {.*}#staticLibs = {$metadataLibs }#"  > "$dstDir/$device/metadata.lua_"
        mv "$dstDir/$device/metadata.lua_" "$dstDir/$device/metadata.lua"
    done
}

function copyPluginContents {

    local srcDir="$1"
    local dstDir="$2"

    if [ ! -d "$srcDir" ]
    then
        echo "Skipping plugin for $srcDir, no source framework found."
        return 0
    fi

    mkdir -p "$dstDir"

    for f in "$srcDir"/*.framework
    do
        [ -e "$f" ] || continue
        extractArchitecturesFramework "$f" "$dstDir"
        mkdir -p "$dstDir/universal"
        "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg -resolve-src-symlinks "$f"  "$dstDir/universal/"
    done

    for a in "$srcDir"/*.a
    do
        [ -e "$a" ] || continue
        bn="$(basename "$a")"
        extractArchitecturesLib "$a" "$bn" "$dstDir"
        mkdir -p "$dstDir/universal"
        "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg -resolve-src-symlinks "$a"  "$dstDir/universal/"
    done

    for device in "iphone" "iphone-sim"
    do
        resDst="$dstDir/$device/resources"

        for b in "$srcDir"/*.bundle
        do
            [ -e "$b" ] || continue
            mkdir -p "$resDst"
            cp -r "$b" "$resDst"
        done

        if [ -d "$srcDir/Resources" ] && [ -n "$(ls "$srcDir/Resources")" ]
        then
            mkdir -p "$resDst"
            cp -r "$srcDir/Resources/." "$resDst"
        fi      
    done
}

function makePlugin {
    local dstDir="$1"
    shift

    mkdir -p "$dstDir"

    for device in "iphone" "iphone-sim"
    do
        if [ -d "$dstDir/$device" ]
        then
            find "$dstDir/$device" ! -name "metadata.lua" -mindepth 1 -delete || true
        fi
    done

    for srcDir in "$@"
    do
        copyPluginContents "$srcDir" "$dstDir"
    done
    makeMetadata "$dstDir"
}

function srcPodCopyHelper {
    local f="$1"
    local PLUGIN_DEST="$2"

    FRAMEWORK_NAME=$(basename "$f")
    BIN_NAME=${FRAMEWORK_NAME%.framework}
    SRC_BIN="$f"/$BIN_NAME

    if [[ $(file "$SRC_BIN" | grep -c "ar archive") -ne 0 ]]; then
        # echo " - $FRAMEWORK_NAME: is a static Framework, extracting."

        DEST_BIN="$PLUGIN_DEST"/$FRAMEWORK_NAME/$BIN_NAME
        "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg --exclude Headers --exclude PrivateHeaders --exclude Modules -resolve-src-symlinks "$f"  "$PLUGIN_DEST"
        stripBitcode "$DEST_BIN"
        rm -rf "$PLUGIN_DEST/$FRAMEWORK_NAME/Versions"
    else
        # echo " + $FRAMEWORK_NAME: embedding"

        mkdir -p "$PLUGIN_DEST"/resources/Frameworks
        DEST_BIN="$PLUGIN_DEST"/resources/Frameworks/$FRAMEWORK_NAME/$BIN_NAME
        "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg --exclude Headers --exclude PrivateHeaders --exclude Modules -resolve-src-symlinks "$f"  "$PLUGIN_DEST"/resources/Frameworks
        stripBitcode "$DEST_BIN"
        rm -rf "$PLUGIN_DEST/resources/Frameworks/$FRAMEWORK_NAME/Versions"
    fi
}

function addSrcPods {

    local dstDir="$1"
    local srcDirPlaceholder="$2"

    srcDirDevice="${srcDirPlaceholder/______/Release-iphoneos}"
    srcDirSim="${srcDirPlaceholder/______/Release-iphonesimulator}"

    if [ ! -d "$srcDirDevice" ] || [ ! -d "$srcDirSim" ]
    then
        echo "Skipping srcPod for $srcDirPlaceholder, no source framework found."
        return 0
    fi

    srcPodCopyHelper "$srcDirDevice" "$dstDir/iphone"
    srcPodCopyHelper "$srcDirSim" "$dstDir/iphone-sim"

    makeMetadata "$dstDir"


    local PLUGIN_DEST="$dstDir/universal"

    local FRAMEWORK_NAME
    FRAMEWORK_NAME=$(basename "$srcDirDevice")
    local BIN_NAME=${FRAMEWORK_NAME%.framework}
    local SRC_BIN="$srcDirDevice/$BIN_NAME"
    local DEST_BIN="$PLUGIN_DEST"/$FRAMEWORK_NAME/$BIN_NAME
    mkdir -p "$PLUGIN_DEST"
    "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg -resolve-src-symlinks "$srcDirDevice"  "$PLUGIN_DEST"
    if lipo "$srcDirSim/$BIN_NAME" -verify_arch arm64
    then
        lipo -remove arm64 "$srcDirSim/$BIN_NAME" -o "$srcDirSim/$BIN_NAME"
    fi
    lipo -create "$srcDirDevice/$BIN_NAME" "$srcDirSim/$BIN_NAME" -o "$DEST_BIN"
    rm -rf "$PLUGIN_DEST/$FRAMEWORK_NAME/Versions"
}

PREV_DIR="$(pwd)"
cd "$ROOT"

# make binaries for plugins

makePlugin "${PLUGINS}/AdColony/plugins/$REV"          "iOSPods/Pods/APDAdColonyAdapter/APDAdColonyAdapter.embeddedframework" "iOSPods/Pods/AdColony"
# makePlugin "${PLUGINS}/Bidmachine/plugins/$REV"        "iOSPods/Pods/APDBidMachineAdapter/APDBidMachineAdapter.embeddedframework"
makePlugin "${PLUGINS}/AmazonAds/plugins/$REV"         "iOSPods/Pods/APDAmazonAdsAdapter/APDAmazonAdsAdapter.embeddedframework" "iOSPods/Pods/AmazonAd/AmazonMobileAds-ios-3.1.0-SDK/"
makePlugin "${PLUGINS}/AppLovin/plugins/$REV"          "iOSPods/Pods/APDAppLovinAdapter/APDAppLovinAdapter.embeddedframework" "iOSPods/Pods/AppLovinSDK/applovin-ios-sdk-6.14.10/"
makePlugin "${PLUGINS}/base/plugins/$REV"              "iOSPods/Pods/Appodeal" "iOSPods/Pods/StackModules" "iOSPods/Pods/StackIAB"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/Protobuf/Protobuf.framework"
# makePlugin "${PLUGINS}/Chartboost/plugins/$REV"        "iOSPods/Pods/APDChartboostAdapter/APDChartboostAdapter.embeddedframework"
makePlugin "${PLUGINS}/FacebookAudience/plugins/$REV"  "iOSPods/Pods/APDFacebookAudienceAdapter/APDFacebookAudienceAdapter.embeddedframework" "iOSPods/Pods/FBAudienceNetwork/Static"
addSrcPods "${PLUGINS}/FacebookAudience/plugins/$REV"  "iOSPods/build/Build/Products/______/FBSDKCoreKit/FBSDKCoreKit.framework"
makePlugin "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/Pods/APDGoogleAdMobAdapter/APDGoogleAdMobAdapter.embeddedframework" "iOSPods/Pods/GoogleAppMeasurement/Frameworks"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/GoogleMobileAds/GoogleMobileAds.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/UserMessagingPlatform/UserMessagingPlatform.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/GoogleUtilities/GoogleUtilities.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/nanopb/nanopb.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/PromisesObjC/FBLPromises.framework"
# makePlugin "${PLUGINS}/InMobi/plugins/$REV"            "iOSPods/Pods/APDInMobiAdapter/APDInMobiAdapter.embeddedframework"
# makePlugin "${PLUGINS}/InnerActive/plugins/$REV"       "iOSPods/Pods/APDInnerActiveAdapter/APDInnerActiveAdapter.embeddedframework"
makePlugin "${PLUGINS}/IronSource/plugins/$REV"        "iOSPods/Pods/APDIronSourceAdapter/APDIronSourceAdapter.embeddedframework" "iOSPods/Pods/IronSourceSDK/IronSource"
# makePlugin "${PLUGINS}/Mobvista/plugins/$REV"          "iOSPods/Pods/APDMintegralAdapter/APDMintegralAdapter.embeddedframework"
makePlugin "${PLUGINS}/MyTarget/plugins/$REV"          "iOSPods/Pods/APDMyTargetAdapter/APDMyTargetAdapter.embeddedframework" "iOSPods/Pods/myTargetSDK/"
makePlugin "${PLUGINS}/Ogury/plugins/$REV"             "iOSPods/Pods/APDOguryAdapter/APDOguryAdapter.embeddedframework" "iOSPods/Pods/OguryAds/OguryAds"
# makePlugin "${PLUGINS}/OpenX/plugins/$REV"             "iOSPods/Pods/APDOpenXAdapter/APDOpenXAdapter.embeddedframework"
# makePlugin "${PLUGINS}/Pubnative/plugins/$REV"         "iOSPods/Pods/APDPubnativeAdapter/APDPubnativeAdapter.embeddedframework"
makePlugin "${PLUGINS}/Smaato/plugins/$REV"            "iOSPods/Pods/APDSmaatoAdapter/APDSmaatoAdapter.embeddedframework" "iOSPods/Pods/smaato-ios-sdk/" "iOSPods/Pods/smaato-ios-sdk/vendor"
makePlugin "${PLUGINS}/StartApp/plugins/$REV"          "iOSPods/Pods/APDStartAppAdapter/APDStartAppAdapter.embeddedframework" "iOSPods/Pods/StartAppSDK"
# makePlugin "${PLUGINS}/Tapjoy/plugins/$REV"            "iOSPods/Pods/APDTapjoyAdapter/APDTapjoyAdapter.embeddedframework"
# makePlugin "${PLUGINS}/TwitterMoPub/plugins/$REV"      "iOSPods/Pods/APDTwitterMoPubAdapter/APDTwitterMoPubAdapter.embeddedframework" "iOSPods/Pods/mopub-ios-sdk/MoPubSDK/Viewability/MOAT" "iOSPods/Pods/mopub-ios-sdk/MoPubSDK/Viewability/Avid"
# addSrcPods "${PLUGINS}/TwitterMoPub/plugins/$REV"      "iOSPods/build/Build/Products/______/mopub-ios-sdk/MoPub.framework"
makePlugin "${PLUGINS}/Unity/plugins/$REV"             "iOSPods/Pods/APDUnityAdapter/APDUnityAdapter.embeddedframework" "iOSPods/Pods/UnityAds"
makePlugin "${PLUGINS}/Vungle/plugins/$REV"            "iOSPods/Pods/APDVungleAdapter/APDVungleAdapter.embeddedframework" "iOSPods/Pods/VungleSDK-iOS"
makePlugin "${PLUGINS}/Yandex/plugins/$REV"            "iOSPods/Pods/APDYandexAdapter/APDYandexAdapter.embeddedframework" "iOSPods/Pods/YandexMobileAds/static" "iOSPods/Pods/YandexMobileMetrica/static"

addSrcPods "$ROOT/JustFrameworks" "iOSPods/build/Build/Products/______/FBSDKLoginKit/FBSDKLoginKit.framework"
addSrcPods "$ROOT/JustFrameworks" "iOSPods/build/Build/Products/______/FBSDKShareKit/FBSDKShareKit.framework"
addSrcPods "$ROOT/JustFrameworks" "iOSPods/build/Build/Products/______/FBSDKCoreKit/FBSDKCoreKit.framework"

makePlugin "$ROOT/Googler"       "iOSPods/Pods/GoogleAppMeasurement/Frameworks" "iOSPods/Pods/Google-Mobile-Ads-SDK/Frameworks/GoogleMobileAdsFramework-Current"
addSrcPods "$ROOT/Googler"       "iOSPods/build/Build/Products/______/GoogleUtilities/GoogleUtilities.framework"
addSrcPods "$ROOT/Googler"       "iOSPods/build/Build/Products/______/nanopb/nanopb.framework"
addSrcPods "$ROOT/Googler"       "iOSPods/build/Build/Products/______/PromisesObjC/FBLPromises.framework"



# Copy built plugin and metadata.lua
if [ -d "${PLUGINS}/base/plugins/$REV/" ] && [ -d "../ios-modular/BuiltPlugin/" ]
then
    cp -R ../ios-modular/BuiltPlugin/ "${PLUGINS}/base/plugins/$REV/"
fi

cd "$PREV_DIR"
