#!/bin/bash -e

REV="2018.3326"
VERSION="2.11.0.1"
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
    local liposWasOK=0
    for arch in $archs; do
        out="$dstDir/${lib%.a}.$arch.a"
        if lipo "$src" -thin "$arch" -output "$out" &> /dev/null; then
            arcOuts+=("$out")
            liposWasOK=1
        fi
    done

    if [ $liposWasOK -eq 1 ]; then
        lipo -create "${arcOuts[@]}" -output "$dstDir/$lib"
        rm -f "${arcOuts[@]}"
        stripBitcode "$dstDir/$lib"
    else
        echo "No architectures to extract from $src ($archs)"
    fi
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

    srcDirDevice="${srcDir/______/Release-iphoneos}"
    srcDirSim="${srcDir/______/Release-iphonesimulator}"
    
    if [ ! -d "$srcDir" ] && [ ! -e "$srcDirDevice" ]
    then
        echo "Skipping plugin for $srcDir $srcDirDevice, no source framework or file found."
        return 0
    fi

    mkdir -p "$dstDir"

    for f in "$srcDir"/*.framework
    do
        [ -e "$f" ] || continue
        SRC_BIN="$f/$(basename "${f%.framework}")"
        if [[ $(file "$SRC_BIN" | grep -c "ar archive") -ne 0 ]]; then
            # echo " - $FRAMEWORK_NAME: is a static Framework, extracting."
            extractArchitecturesFramework "$f" "$dstDir"
            mkdir -p "$dstDir/universal"
            "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg -resolve-src-symlinks "$f"  "$dstDir/universal/"
        else
            addSrcPods "$dstDir"      "$f"
        fi
    done

    for a in "$srcDir"/*.a 
    do
        [ -e "$a" ] || continue
        bn="$(basename "$a")"
        extractArchitecturesLib "$a" "$bn" "$dstDir"
        mkdir -p "$dstDir/universal"
        "$(xcrun -f rsync)" --links --exclude '*.xcconfig' --exclude _CodeSignature --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude .hg -resolve-src-symlinks "$a"  "$dstDir/universal/"
    done

    for deviceFile in "$srcDirDevice" "$srcDirSim"
    do
        
        if [[ "$deviceFile" == *"Release-"* ]]; then
            local deviceDst="iphone"
            mkdir -p "$dstDir"
            if [[ "$deviceFile" == *"iphonesimulator"* ]]; then
                deviceDst="iphone-sim"
            fi
            cp -r "$deviceFile" "$dstDir/$deviceDst"
        fi
        
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
    if [ "$srcDirSim" != "$srcDirDevice" ]
    then
        if lipo "$srcDirSim/$BIN_NAME" -verify_arch arm64
        then
            lipo -remove arm64 "$srcDirSim/$BIN_NAME" -o "$srcDirSim/$BIN_NAME"
        fi
        lipo -create "$srcDirDevice/$BIN_NAME" "$srcDirSim/$BIN_NAME" -o "$DEST_BIN"
    fi
    rm -rf "$PLUGIN_DEST/$FRAMEWORK_NAME/Versions"
}

cd "$ROOT"

# make binaries for plugins

makePlugin "${PLUGINS}/base/plugins/$REV"              "iOSPods/Pods/Appodeal" "iOSPods/Pods/StackIAB"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/StackAnalytics/Base/StackAnalytics.framework"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/StackAnalytics/Crashes/StackCrashReporter.framework"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/StackIAB/StackIAB.framework"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/StackModules/StackModules.framework"
addSrcPods "${PLUGINS}/base/plugins/$REV"              "iOSPods/build/Build/Products/______/Protobuf/Protobuf.framework"


makePlugin "${PLUGINS}/AdColony/plugins/$REV"          "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDAdColonyAdapter/libAPDAdColonyAdapter.a" "iOSPods/Pods/AdColony"

makePlugin "${PLUGINS}/AmazonAds/plugins/$REV"         "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDAmazonAdsAdapter/libAPDAmazonAdsAdapter.a" "iOSPods/Pods/AmazonAd/AmazonMobileAds-ios-3.1.0-SDK/" "iOSPods/Pods/AmazonPublisherServicesSDK/APS_iOS_SDK-3.3.0/"

makePlugin "${PLUGINS}/AppLovin/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDAppLovinAdapter/libAPDAppLovinAdapter.a" "iOSPods/Pods/AppLovinSDK/applovin-ios-sdk-10.3.7"
addSrcPods "${PLUGINS}/AppLovin/plugins/$REV"          "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/AppLovinSDK/AppLovinSDK.framework"

makePlugin "${PLUGINS}/Bidmachine/plugins/$REV"        "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDBidMachineAdapter/libAPDBidMachineAdapter.a" "iOSPods/Pods/BidMachine"
addSrcPods "${PLUGINS}/Bidmachine/plugins/$REV"        "iOSPods/build/Build/Products/______/CriteoPublisherSdk/CriteoPublisherSdk.framework"


makePlugin "${PLUGINS}/FacebookAudience/plugins/$REV"  "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDFacebookAudienceAdapter/libAPDFacebookAudienceAdapter.a" "iOSPods/Pods/FBAudienceNetwork/Static"
addSrcPods "${PLUGINS}/FacebookAudience/plugins/$REV"  "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKCoreKit/FBSDKCoreKit.framework"
addSrcPods "${PLUGINS}/FacebookAudience/plugins/$REV"  "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKCoreKit_Basics/FBSDKCoreKit_Basics.framework"

makePlugin "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDGoogleAdMobAdapter/libAPDGoogleAdMobAdapter.a"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/PromisesObjC/FBLPromises.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/GoogleAppMeasurement/WithoutAdIdSupport/GoogleAppMeasurement.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/GoogleAppMeasurement/AdIdSupport/GoogleAppMeasurementIdentitySupport.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/Google-Mobile-Ads-SDK/GoogleMobileAds.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/GoogleUtilities/GoogleUtilities.framework"
addSrcPods "${PLUGINS}/GoogleAdMob/plugins/$REV"       "iOSPods/build/Build/Products/______/nanopb/nanopb.framework"



makePlugin "${PLUGINS}/IronSource/plugins/$REV"        "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDIronSourceAdapter/libAPDIronSourceAdapter.a" "iOSPods/Pods/IronSourceSDK/IronSource"


makePlugin "${PLUGINS}/MyTarget/plugins/$REV"          "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDMyTargetAdapter/libAPDMyTargetAdapter.a"
addSrcPods "${PLUGINS}/MyTarget/plugins/$REV"          "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/MyTargetSDK/MyTargetSDK.framework"

makePlugin "${PLUGINS}/Ogury/plugins/$REV"             "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDOguryAdapter/libAPDOguryAdapter.a" "iOSPods/Pods/OguryAds/OguryAds"
addSrcPods "${PLUGINS}/Ogury/plugins/$REV"             "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/OguryAds/OguryAds.framework"

makePlugin "${PLUGINS}/Unity/plugins/$REV"             "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDUnityAdapter/libAPDUnityAdapter.a" "iOSPods/Pods/UnityAds"

makePlugin "${PLUGINS}/Vungle/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDVungleAdapter/libAPDVungleAdapter.a"
addSrcPods "${PLUGINS}/Vungle/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/VungleSDK-iOS/VungleSDK.framework"

makePlugin "${PLUGINS}/Yandex/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/APDYandexAdapter/libAPDYandexAdapter.a" "iOSPods/Pods/YandexMobileAds/static" "iOSPods/Pods/YandexMobileAds/static/YandexMobileAds.framework"
addSrcPods "${PLUGINS}/Yandex/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/YandexMobileMetrica/Static/Core/YandexMobileMetrica.framework"
addSrcPods "${PLUGINS}/Yandex/plugins/$REV"            "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/YandexMobileMetrica/Static/Crashes/YandexMobileMetricaCrashes.framework"

#makePlugin "${PLUGINS}/Smaato/plugins/$REV"            "iOSPods/Pods/APDSmaatoAdapter/APDSmaatoAdapter-${VERSION}/APDSmaatoAdapter.xcframework" "iOSPods/Pods/smaato-ios-sdk" "iOSPods/Pods/smaato-ios-sdk/vendor"
#makePlugin "${PLUGINS}/TwitterMoPub/plugins/$REV"      "iOSPods/Pods/APDTwitterMoPubAdapter/APDTwitterMoPubAdapter.embeddedframework"
#addSrcPods "${PLUGINS}/TwitterMoPub/plugins/$REV"      "iOSPods/build/Build/Products/______/mopub-ios-sdk/MoPub.framework"
#makePlugin "${PLUGINS}/Tapjoy/plugins/$REV"            "iOSPods/Pods/APDTapjoyAdapter/APDTapjoyAdapter.embeddedframework" "iOSPods/Pods/TapjoySDK/TapjoySDK_iOS_v12.7.0/Libraries/Tapjoy.embeddedframework" "iOSPods/Pods/TapjoySDK/TapjoySDK_iOS_v12.7.0/Libraries/Tapjoy.embeddedframework/Tapjoy.framework/Versions/A/Resources"
# makePlugin "${PLUGINS}/StartApp/plugins/$REV"          "iOSPods/Pods/APDStartAppAdapter/APDStartAppAdapter.embeddedframework" "iOSPods/Pods/StartAppSDK"
# makePlugin "${PLUGINS}/Mobvista/plugins/$REV"          "iOSPods/Pods/APDMintegralAdapter/APDMintegralAdapter.embeddedframework" "iOSPods/Pods/MintegralAdSDK/Fmk"
# makePlugin "${PLUGINS}/InMobi/plugins/$REV"            "iOSPods/Pods/APDInMobiAdapter/APDInMobiAdapter.embeddedframework" "iOSPods/Pods/InMobiSDK"
#makePlugin "${PLUGINS}/Chartboost/plugins/$REV"        "iOSPods/Pods/APDChartboostAdapter/APDChartboostAdapter.embeddedframework" "iOSPods/Pods/ChartboostSDK"
# makePlugin "${PLUGINS}/InnerActive/plugins/$REV"       "iOSPods/Pods/APDInnerActiveAdapter/APDInnerActiveAdapter.embeddedframework"
# makePlugin "${PLUGINS}/OpenX/plugins/$REV"             "iOSPods/Pods/APDOpenXAdapter/APDOpenXAdapter.embeddedframework"
# # makePlugin "${PLUGINS}/Pubnative/plugins/$REV"         "iOSPods/Pods/APDPubnativeAdapter/APDPubnativeAdapter.embeddedframework"

makePlugin "$ROOT/Facebook"     "iOSPods/Pods/FBAudienceNetwork/Static"
addSrcPods "$ROOT/Facebook"     "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKLoginKit/FBSDKLoginKit.framework"
addSrcPods "$ROOT/Facebook"     "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKShareKit/FBSDKShareKit.framework"
addSrcPods "$ROOT/Facebook"     "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKCoreKit/FBSDKCoreKit.framework"
addSrcPods "$ROOT/Facebook"     "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FBSDKCoreKit_Basics/FBSDKCoreKit_Basics.framework"

makePlugin "$ROOT/Google"       "iOSPods/Pods/APDGoogleAdMobAdapter/APDGoogleAdMobAdapter-${VERSION}/APDGoogleAdMobAdapter.xcframework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseABTesting/FirebaseABTesting.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseCore/FirebaseCore.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseCoreDiagnostics/FirebaseCoreDiagnostics.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseInstallations/FirebaseInstallations.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseMessaging/FirebaseMessaging.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/FirebaseRemoteConfig/FirebaseRemoteConfig.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/GoogleDataTransport/GoogleDataTransport.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/GoogleUtilities/GoogleUtilities.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/nanopb/nanopb.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/PromisesObjC/FBLPromises.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/FirebaseAnalytics/AdIdSupport/FirebaseAnalytics.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/GoogleAppMeasurement/WithoutAdIdSupport/GoogleAppMeasurement.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/GoogleAppMeasurement/AdIdSupport/GoogleAppMeasurementIdentitySupport.framework"
addSrcPods "$ROOT/Google"       "iOSPods/build/Build/Products/______/XCFrameworkIntermediates/Google-Mobile-Ads-SDK/GoogleMobileAds.framework"


# Copy built plugin and metadata.lua
if [ -d "${PLUGINS}/base/plugins/$REV/" ] && [ -d "../ios-modular/BuiltPlugin/" ]
then
    true
    cp -R ../ios-modular/BuiltPlugin/ "${PLUGINS}/base/plugins/$REV/"
fi

cd "$PREV_DIR"