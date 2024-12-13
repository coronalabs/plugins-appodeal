//
//  Appodeal.h
//  Appodeal
//
//  AppodealSDK version 3.4.0
//
//  Copyright (c) 2024 Appodeal, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Appodeal/APDDefines.h>
#import <Appodeal/APDSdk.h>
#import <Appodeal/APDActivityLog.h>

#import <Appodeal/APDInterstitialAd.h>
#import <Appodeal/APDRewardProtocol.h>
#import <Appodeal/APDRewardedVideo.h>

#import <Appodeal/APDMRECView.h>
#import <Appodeal/APDBannerView.h>

#import <Appodeal/APDNativeAdViewProtocol.h>
#import <Appodeal/APDNativeAdQueue.h>
#import <Appodeal/APDNativeAd.h>
#import <Appodeal/APDImage.h>

#if __has_include(<StackConsentManager/StackConsentManager.h>)
#import <StackConsentManager/StackConsentManager.h>
#endif
/**
 Appodeal ads SDK
 */
@interface Appodeal : NSObject
/**
 Unavailable initializer
 @return nil
 */
+ (instancetype _Nonnull)alloc NS_UNAVAILABLE;
/**
 Unavailable initializer
 @return nil
 */
- (instancetype _Nonnull)init NS_UNAVAILABLE;
/**
 Unavailable initializer
 @return nil
 */
+ (instancetype _Nonnull)new NS_UNAVAILABLE;
/**
 Return all registred networks name
 @note Objective-C
 <pre> [Appodeal registeredNetworkNames]; </pre>
 @note Swift
 <pre> Appodeal.registeredNetworkNames() </pre>
 @return registred networks name
 */
+ (NSArray <NSString *>*_Nonnull)registeredNetworkNames;
/**
 Return registred networks names for specific ad type
 @note Objective-C
 <pre> [Appodeal registeredNetworkNamesForAdType:AppodealAdTypeBanner]; </pre>
 @note Swift
 <pre> Appodeal.registeredNetworkNamesForAdType(.banner) </pre>
 @return registred networks names
 */
+ (NSArray<NSString *> *_Nonnull)registeredNetworkNamesForAdType:(AppodealAdType)adType;
/**
 To disable a networks use this method
 @note Objective-C
 <pre> [Appodeal disableNetworks:@[@"YOUR_NETWORK_NAME"]]; </pre>
 @note Swift
 <pre> Appodeal.disableNetwork(["YOUR_NETWORK_NAME"]) </pre>
 @warning Use method before initialization!
 @param networks Array of Networks name
 */
+ (void)disableNetworks:(NSArray <NSString *>* _Nullable)networks;
/**
 To disable a networks of type use this method
 @note Objective-C
 <pre> [Appodeal disableNetworks:@[@"YOUR_NETWORK_NAME"] forAdType:AppodealAdType]; </pre>
 @note Swift
 <pre> Appodeal.disableNetwork(["YOUR_NETWORK_NAME"], adType:AppodealAdType) </pre>
 @warning Use method before initialization!
 @param networks Array of Networks name
 @param adType AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeMREC, AppodealAdTypeNonSkippableVideo
 */
+ (void)disableNetworks:(NSArray <NSString *>* _Nullable)networks forAdType:(AppodealAdType)adType;
/**
 To disable a network use this method
 @note Objective-C
 <pre> [Appodeal disableNetwork:@"YOUR_NETWORK_NAME"]; </pre>
 @note Swift
 <pre> Appodeal.disableNetwork("YOUR_NETWORK_NAME") </pre>
 @warning Use method before initialization!
 @param networkName Network name to disable
 */
+ (void)disableNetwork:(nonnull NSString *)networkName;
/**
 To disable a network use this method
 @note Objective-C
 <pre> [Appodeal disableNetworkForAdType:AppodealAdTypeInterstitial name:@"YOUR_NETWORK_NAME"]; </pre>
 @note Swift
 <pre> Appodeal.disableNetworkForAdType(AppodealAdType.Interstitial, name: "YOUR") </pre>
 @warning Use method before initialization!
 @param adType AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeMREC, AppodealAdTypeNonSkippableVideo
 @param networkName Use network name
 */
+ (void)disableNetworkForAdType:(AppodealAdType)adType name:(nonnull NSString *)networkName;
/**
 Get predicted eCPM for type and defualt placement
 @param type AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeNonSkippableVideo
 @return predicted eCPM
 */
+ (double)predictedEcpmForAdType:(AppodealAdType)type;
/**
 Get predicted eCPM for type
 @param type AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeNonSkippableVideo
 @param placement String placement name
 @return predicted eCPM
 */
+ (double)predictedEcpmForAdType:(AppodealAdType)type placement:(nonnull NSString *)placement;
/**
 Set flag NO if you have disabled locationTracking, and YES that enabled
 @note To disable location check, use this method
 @note Objective-C
 <pre> [Appodeal setLocationTracking:YES]; </pre>
 @note Swift
 <pre> Appodeal.setLocationTracking(true) </pre>
 @warning Use method before initialization!
 @param enabled flag
 */
+ (void)setLocationTracking:(BOOL)enabled;
/**
 Enable/disable autocache
 @note After initializing the SDK, start caching ads of those types that were enabled as autocache
 Default autocache enabled for AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeRewardedVideo or AppodealAdTypeNonSkippableVideo
 Also you can do something like this to disable autocache:
 @note Objective-C
 <pre> [Appodeal setAutocache: NO types: AppodealAdTypeInterstitial | AppodealAdTypeRewardedVideo] </pre>
 @note Swift
 <pre> Appodeal.setAutocache(false, types: AppodealAdType.Interstitial) </pre>
 @warning Use method before initialization!
 @param autocache Bolean flag
 @param types AppodealAdTypeRewardedVideo or AppodealAdTypeNonSkippableVideo, AppodealAdTypeInterstitial
 */
+ (void)setAutocache:(BOOL)autocache types:(AppodealAdType)types;
/**
 Get autocache enablement
 @note Objective-C
 <pre> [Appodeal isAutocacheEnabled:AppodealAdTypeInterstitial]; </pre>
 @note Swift
 <pre> Appodeal.isAutocacheEnabled(AppodealAdType.Interstitial) </pre>
 @warning After initialization!
 @param types AppodealAdTypeRewardedVideo, AppodealAdTypeInterstitial
 @return If enabled return YES or NO if not
 */
+ (BOOL)isAutocacheEnabled:(AppodealAdType)types;
/**
 Initialize method. To initialize Appodeal with several types you
 user consent on personal data processing assumes to be true
 can do something like this:
 @note Objective-C
 <pre> [Appodeal initializeWithApiKey:YOUR_API_KEY types: AppodealAdTypeInterstitial | AppodealAdTypeRewardedVideo]; </pre>
 @note Swift
 <pre>
 let adTypes: AppodealAdType = [.banner, .interstitial]
 Appodeal.initialize(withApiKey: "API_KEY", types: adTypes) </pre>
 @param apiKey Your api key from Appodeal Dashboard
 @param types  Appodeal ad type
 */
+ (void)initializeWithApiKey:(nonnull NSString *)apiKey types:(AppodealAdType)types;
/**
 Disable calls of precache callbacks
 @note Objective-C
 <pre> [Appodeal setTriggerPrecacheCallbacks:YES]; </pre>
 @note Swift
 <pre> Appodeal.setTriggerPrecacheCallbacks(true) </pre>
 @param shouldTrigger Bolean flag indicates that precache callbacks are disabled or not
 */
+ (void)setTriggerPrecacheCallbacks:(BOOL)shouldTrigger;
/**
 Disable calls of precache callbacks for AppodealAdTypes
 @note Objective-C
 <pre> [Appodeal setTriggerPrecacheCallbacks:YES types: AppodealAdTypeInterstitial | AppodealAdTypeRewardedVideo]; </pre>
 @note Swift
 <pre> Appodeal.setTriggerPrecacheCallbacks(true, types: [.interstitial, .rewardedVideo) </pre>
 @param shouldTrigger Bolean flag indicates that precache callbacks are disabled or not
 @param types  Appodeal ad type
 */
+ (void)setTriggerPrecacheCallbacks:(BOOL)shouldTrigger types:(AppodealAdType)types;
/**
 Get that SDK initialized
 @note Objective-C
 <pre> [Appodeal isInitializedForAdType:AppodealAdTypeInterstitial]; </pre>
 @note Swift
 <pre> isInitializedForAdType(.Interstitial) </pre>
 @warning Use method after initialization!
 @param type Type you want to check on initialisation.
 @return YES if sdk initialized or NO if not. In this method used strict compare!
 */
+ (BOOL)isInitializedForAdType:(AppodealAdType)type;
/**
 Appodeal supports multiple log levels for internal logging,
 and ONLY one (VERBOSE) log level for third party ad networks.
 To enable third party ad networks logging, set log level to APDLogLevelVerbose.
 If log level other than APDLogLevelVerbose, all third party ad networks logging will be suppressed (if possible).
 *
 @param logLevel APDLogLevel value
 */
+ (void)setLogLevel:(APDLogLevel)logLevel;
/**
 Set framework type before initialization!
 @note Objective-C
 <pre> [Appodeal setFramework:APDFrameworkNative version:@"5.1"]; </pre>
 @note Swift
 <pre> Appodeal.setFramework(APDFramework.native, "5.1") </pre>
 @param framework Framework type, default is iOS Native SDK
 @param version Framework version. Default nill
 */
+ (void)setFramework:(APDFramework)framework version:(nullable NSString *)version;
/**
 Set plugin version use before initialization!
 @note Objective-C
 <pre> [Appodeal setPluginVersion:@"1.0.0"]; </pre>
 @note Swift
 <pre> Appodeal.setPluginVersion("1.0.0") </pre>
 @param pluginVersion -  NSString value, default nil
 */
+ (void)setPluginVersion:(nonnull NSString *)pluginVersion;
/**
 Set custom extra value for specific key
 @note Objective-C
 <pre> [Appodeal setExtrasValue:@"bar" forKey:@"foo"]; </pre>
 @note Swift
 <pre> Appodeal.setExtrasValue("bar", forKey:"foo"]) </pre>
 @param value JSON encodable object. Might be nil
 @param key Nonnull string value
 */
+ (void)setExtrasValue:(nullable id)value forKey:(nonnull NSString *)key;
/**
 SDK extras
 @note Objective-C
 <pre>
 NSDictionary *customState = [Appodeal extras];
 </pre>
 @note Swift
 <pre>
 let customState = Appodeal.extras()
 </pre>
 */
+ (nullable NSDictionary <NSString *, id> *)extras;
/**
 Set activity delegate
 @param activityDelegate Nullable instance of class that conforms protocol APDActivityDelegate
 */
+ (void)setActivityDelegate:(nullable id<APDActivityDelegate>)activityDelegate;
/**
 Set initialization delegate
 @param initializationDelegate Nullable instance of class that conforms protocol AppodealInitializationDelegate
 */
+ (void)setInitializationDelegate:(nullable id<AppodealInitializationDelegate>)initializationDelegate;
/**
 Set ad revenue delegate
 @param adRevenueDelegate Nullable instance of class that conforms protocol AppodealAdRevenueDelegate
 */
+ (void)setAdRevenueDelegate:(nullable id<AppodealAdRevenueDelegate>)adRevenueDelegate;
/**
 Set interstitial delegate to get callbacks
 @note Objective-C
 <pre> [Appodeal setInterstitialDelegate:self]; </pre>
 @note Swift
 <pre> Appodeal.setInterstitialDelegate(self) </pre>
 @warning Use method before or after initialization!
 @param interstitialDelegate Object that implement AppodealInterstitialDelegate protocol
 */
+ (void)setInterstitialDelegate:(nullable id<AppodealInterstitialDelegate>)interstitialDelegate;
/**
 Set banner delegate to get callbacks
 @note Objective-C
 <pre> [Appodeal setBannerDelegate:self]; </pre>
 @note Swift
 <pre> Appodeal.setBannerDelegate(self) </pre>
 @warning Use method before or after initialization!
 @param bannerDelegate Object that implements AppodealBannerDelegate protocol
 */
+ (void)setBannerDelegate:(nullable id<AppodealBannerDelegate>)bannerDelegate;
/**
 Set rewarded video delegate to get callbacks
 @note Objective-C
 <pre> [Appodeal setRewardedVideoDelegate:self]; </pre>
 @note Swift
 <pre> Appodeal.setRewardedVideoDelegate(self) </pre>
 @warning Use method before or after initialization!
 @param rewardedVideoDelegate Object that implements AppodealRewardedVideoDelegate protocol
 */
+ (void)setRewardedVideoDelegate:(nullable id<AppodealRewardedVideoDelegate>)rewardedVideoDelegate;
/**
 Set non skippable video delegate to get callbacks
 @note Objective-C
 <pre> [Appodeal setNonSkippableVideoDelegate:self]; </pre>
 @note Swift
 <pre> Appodeal.setNonSkippableVideoDelegate(self) </pre>
 @warning Use method before or after initialization!
 @param nonSkippableVideoDelegate Object that implements AppodealNonSkippableVideoDelegate protocol
 */
+ (void)setNonSkippableVideoDelegate:(nullable id<AppodealNonSkippableVideoDelegate>)nonSkippableVideoDelegate;
/**
 *  Setup preferred banner size for show styles AppodealShowStyleBannerBottom, AppodealShowStyleBannerTop
 *  method not affect APDBannerView or AppodealBannerView. Method can be called before Appodeal initialisation
 *  by defualt preferred banner size is kAppodealUnitSize_320x50 for phones and kAppodealUnitSize_728x90 for tab
 *  @warning If method was called after initialisation, sdk doesn't clear any caches and can show already cached banner
 *  @discussion Objective-C
 *  @code [Appodeal setPreferredBannerAdSize:kAppodealUnitSize_320x50]; @endcode
 *  @discussion Swift
 *  @code Appodeal.setPreferredBannerAdSize(kAppodealUnitSize_320x50) @endcode
 *  @param adSize - Preferred banner size
 */
+ (void)setPreferredBannerAdSize:(APDUnitSize)adSize;
/**
 Appodeal banner view to custom placement
 @note Objective-C
 <pre> [Appodeal banner]; </pre>
 @note Swift
 <pre> Appodeal.banner() </pre>
 @warning We highly recommend to use APDSdk and APDBannerView if you want to get custom placement of banner ads in your app
 @return View that contains banner ad
 */
+ (nullable UIView *)banner;
/**
 If an ad of this type is ready, the ad shows at once. But if not, an ad starts caching and shows after caching, if it has time to within 3 seconds.
 @note Objective-C
 <pre> [Appodeal showAd:AppodealAdTypeInterstitial rootViewController:UIViewController]; </pre>
 @note Swift
 <pre> Appodeal.showAd(AppodealShowStyle.Interstitial, rootViewController: UIViewController!) </pre>
 @param style              AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeMREC, AppodealAdTypeNonSkippableVideo
 @param rootViewController Controller for present ads. If contoller is nil SDK will use own window for present fullscreen ad and root controller of key window for in line ads
 @return YES if possible to show or NO if not
 */
+ (BOOL)showAd:(AppodealShowStyle)style rootViewController:(nullable UIViewController *)rootViewController;
/**
 If an ad of this type is ready, the ad shows at once. But if not, an ad starts caching and shows after caching, if it has time to within 3 seconds.
 @see <pre> + (BOOL)showAd:(AppodealShowStyle)style rootViewController:(UIViewController *)rootViewController;</pre>
 @note Objective-C
 <pre> [Appodeal showAd:AppodealAdTypeInterstitial forPlacement:@"PLACEMENT" rootViewController:UIViewController]; </pre>
 @note Swift
 <pre> Appodeal.showAd(AppodealShowStyle.Interstitial, forPlacement: String!, rootViewController: UIViewController!) </pre>
 @param style AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeMREC, AppodealAdTypeNonSkippableVideo
 @param placement Placement name configured in segments settings on Appodeal Dashboard
 @param rootViewController Controller for present ads. If contoller is nil SDK will use own window for present fullscreen ad and root controller of key window for in line ads
 @return YES if possible to show or NO if not
 */
+ (BOOL)showAd:(AppodealShowStyle)style forPlacement:(nonnull NSString *)placement rootViewController:(nullable UIViewController *)rootViewController;
/**
 Checker for ad is ready and can be shown by current placement
 @note Objective-C
 <pre> [Appodeal canShow:AppodealAdTypeInterstitial forPlacement:MY_PLACEMENT]; </pre>
 @note Swift
 <pre> Appodeal.canShowAd(AppodealShowStyle.Interstitial, forPlacement:MY_PLACEMENT) </pre>
 @param type AppodealAdTypeInterstitial, AppodealAdTypeRewardedVideo, AppodealAdTypeBanner, etc
 @param placement String placement name from dashboard
 @return YES if possible to show or NO if not
 */
+ (BOOL)canShow:(AppodealAdType)type forPlacement:(nonnull NSString *)placement;
/**
 Return reward object currencyName as NSString, and amount as NSUInteger
 */
+ (nonnull id<APDReward>)rewardForPlacement:(nonnull NSString *)placement;
/**
 Start caching an ad for type; if autocache is disabled,
 start loading for default placement
 Ad will not be shown after loading
 @note Objective-C
 <pre> [Appodeal cacheAd:AppodealAdTypeInterstitial]; </pre>
 @note Swift
 <pre> Appodeal.cacheAd(AppodealAdType.Interstitial) </pre>
 @param type AppodealAdTypeInterstitial, AppodealAdTypeBanner, AppodealAdTypeNativeAd, AppodealAdTypeRewardedVideo, AppodealAdTypeMREC, AppodealAdTypeNonSkippableVideo
 */
+ (void)cacheAd:(AppodealAdType)type;
/**
 Hide banner if on screen
 @note Objective-C
 <pre> [Appodeal hideBanner]; </pre>
 @note Swift
 <pre> Appodeal.hideBanner() </pre>
 */
+ (void)hideBanner;
/**
 Enable testing mode.
 In this mode you will get a test ad with <b>eCPM = 0$</b>
 @note Objective-C
 <pre> [Appodeal setTestingEnabled:YES]; </pre>
 @note Swift
 <pre> Appodeal.setTestingEnabled(true) </pre>
 @warning Use method before initialization!
 @param testingEnabled Bolean flag
 */
+ (void)setTestingEnabled:(BOOL)testingEnabled;
/**
 In-app purchase tracking.
 Call this method after user makes an in-app purchase
 @param amount Amount of in-app purchase, for example @0.99
 @param currency In-app purchase currency, for example @"USD"
 */
+ (void)trackInAppPurchase:(nonnull NSNumber *)amount
                  currency:(nonnull NSString *)currency;
/**
 Validate and track in app purchase
 @param productId Identifier of product
 @param type Type of product
 @param price Product price
 @param currency Price currency
 @param transactionId Identifier of payment transaction
 @param additionalParameters Custom parameters
 @param success Succes block
 @param failure Failure block
 */
+ (void)validateAndTrackInAppPurchase:(nullable NSString *)productId
                                 type:(APDPurchaseType)type
                                price:(nullable NSString *)price
                             currency:(nullable NSString *)currency
                        transactionId:(nullable NSString *)transactionId
                 additionalParameters:(nullable NSDictionary *)additionalParameters
                              success:(void (^ _Nullable)(NSDictionary * _Nullable response))success
                              failure:(void (^ _Nullable)(NSError * _Nullable error))failure;
/**
 Track custom event
 @param event Event name
 @param customParameters Custom parameters
 */
+ (void)trackEvent:(nonnull NSString *)event
  customParameters:(NSDictionary * _Nullable)customParameters;
/**
 Get current SDK version
 @note Objective-C
 <pre> [Appodeal getVersion]; </pre>
 @note Swift
 <pre> Appodeal.getVersion() </pre>
 @return Current SDK version
 */
+ (nonnull NSString *)getVersion;
/**
 Check that ad is ready to show
 @note Objective-C
 <pre> [Appodeal isReadyForShowWithStyle:AppodealShowStyleInterstitial]; </pre>
 @note Swift
 <pre> Appodeal.isReadyForShowWithStyle(AppodealShowStyle.Interstitial) </pre>
 @param showStyle AppodealShowStyleInterstitial, AppodealShowStyleVideoOrInterstitial, AppodealShowStyleBannerTop, AppodealShowStyleBannerBottom, AppodealShowStyleRewardedVideo, AppodealShowStyleNonSkippableVideo
 @return YES if ready or NO if not
 */
+ (BOOL)isReadyForShowWithStyle:(AppodealShowStyle)showStyle;
/**
 Check that ad is precache ad or not for given ad type and default placement
 @note Objective-C
 <pre> [Appodeal isPrecacheAd:AppodealAdTypeInterstitial]; </pre>
 @note Swift
 <pre> Appodeal.isPrecacheAd(.interstitial) </pre>
 @param adType One of supported ad type. Not pass mask that contains several types!
 @return YES if loaded ad is precache or NO if ad not loaded or loaded simple ad
 */
+ (BOOL)isPrecacheAd:(AppodealAdType)adType;
/**
 Check that ad is precache ad or not for given ad type and placement
 @note Objective-C
 <pre> [Appodeal isPrecacheAd:AppodealAdTypeInterstitial placement:@"my_placement"]; </pre>
 @note Swift
 <pre> Appodeal.isPrecacheAd(.interstitial, placement: "my_placement") </pre>
 @param adType One of supported ad type. Not pass mask that contains several types!
 @param placement String placement name
 @return YES if loaded ad is precache or NO if ad not loaded or loaded simple ad
 */
+ (BOOL)isPrecacheAd:(AppodealAdType)adType placement:(nonnull NSString *)placement;
/**
 You can set custom rule by using this method. This method will override
 only custom state for specific state.
 Configure filters for segments/placements in <b>Appodeal Dashboard</b>.
 @note For example, you want to create a segment of users who complete 20 or more levels
 You create a rule in the dashboard with name "completedLevels" of type Int,
 operator GreaterThanOrEqualTo and value 10, and then you implement the following code:
 @note Objective-C
 <pre>
 [Appodeal setCustomStateValue:CURRENT_NUMBER_OF_COMPLETED_LEVELS forKey:@"completedLevels"];
 </pre>
 @note Swift
 <pre>
 Appodeal.setCustomStateValue(CURRENT_NUMBER_OF_COMPLETED_LEVELS, forKey:"completedLevels")
 </pre>
 Call this method any time you want, segments change dynamically
 @note And then CURRENT_NUMBER_OF_COMPLETED_LEVELS become 10 or greater
 Your segments settings become available
 @param value JSON encodable object. Might be nil
 @param key Nonnull string value
 */
+ (void)setCustomStateValue:(nullable id)value forKey:(nonnull NSString *)key;
/**
 You can retrieve all passed custom state by using this method.
 @note Objective-C
 <pre>
 NSDictionary *customState = [Appodeal customState];
 </pre>
 @note Swift
 <pre>
 let customState = Appodeal.customState()
 </pre>
 */
+ (nullable NSDictionary <NSString *, id> *)customState;
/**
 Autoresized banner support. Default set to YES;
 @warning Call this method before caching banners!
 @note Objective-C
 <pre> [Appodeal setSmartBannersEnabled:YES]; </pre>
 @note Swift
 <pre> Appodeal.setSmartBannersEnabled(true) </pre>
 @param smartBannerEnabled If YES, the banner will resize depending on screen size. If NO, the banner has a fixed size (320x50 on iPhone and 728x90 on iPad)
 */
+ (void)setSmartBannersEnabled:(BOOL)smartBannerEnabled;
/**
 Return the BOOL value of smart banners active state
 @note Objective-C
 <pre> [Appodeal isSmartBannersEnadled]; </pre>
 @note Swift
 <pre> Appodeal.isSmartBannersEnadled() </pre>
 */
+ (BOOL)isSmartBannersEnabled;
/**
 Banner animation setter. Default set to YES
 @note Objective-C
 <pre> [Appodeal setBannerAnimationEnabled:YES]; </pre>
 @note Swift
 <pre> Appodeal.setBannerAnimationEnabled(true) </pre>
 @warning Call this method before caching banners!
 @param bannerAnimationEnabled If YES, the banner will refresh with animation (UIViewAnimationOptionTransitionCrossDissolve). If NO, the banner will refresh without animation;
 */
+ (void)setBannerAnimationEnabled:(BOOL)bannerAnimationEnabled;
/**
 Banner rotation angles for left and right show styles. Default leftRotationAngleDegrees equals to 90,
 rightRotationAngleDegrees equals to 270
 @note Objective-C
 <pre> [Appodeal setBannerLeftRotationAngleDegrees:-90 rightRotationAngleDegrees: 90]; </pre>
 @warning Call this method before caching banners!
 @param leftRotationAngleDegrees Angle for rotation transform of banner for AppodealShowStyleBannerLeft
 @param rightRotationAngleDegrees Angle for rotation transform of banner for AppodealShowStyleBannerRight
 */
+ (void)setBannerLeftRotationAngleDegrees:(CGFloat)leftRotationAngleDegrees
                rightRotationAngleDegrees:(CGFloat)rightRotationAngleDegrees;
/**
 Enable COPPA setting flag. By defualt this setting is false
 @param childDirectedTreatment Boolean flag inficates that app for kids.
 */
+ (void)setChildDirectedTreatment:(BOOL)childDirectedTreatment;
/**
 Get framework type
 @note Objective-C
 <pre> [Appodeal framework]; </pre>
 @note Swift
 <pre> Appodeal.framework() </pre>
 */
+ (APDFramework)framework;
/**
 Get framework version
 @note Objective-C
 <pre> [Appodeal frameworkVersion]; </pre>
 @note Swift
 <pre> Appodeal.frameworkVersion() </pre>
 */
+ (nullable NSString *)frameworkVersion;
/**
 Get plugin version
 @note Objective-C
 <pre> [Appodeal pluginVersion]; </pre>
 @note Swift
 <pre> Appodeal.pluginVersion() </pre>
 */
+ (nullable NSString *)pluginVersion;
/**
 Get current user segment id
 @note Objective-C
 <pre> [Appodeal segmentId]; </pre>
 @note Swift
 <pre> Appodeal.segmentId() </pre>
 */
+ (nonnull NSNumber *)segmentId;
/**
 Pause all curent sdk work. All mediation task will invalidate asap and your get
 callbacks on fail to load. If SDK currently has loaded ad - it will
 be release and sdk fire expire events. Also autocache will be disabled.
 Call this method to reduce RAM and CPU
 usage in high load placec in your app.
 */
+ (void)pause NS_UNAVAILABLE;
/**
 Resume SDK work after pause. Autocache state turn back.
 */
+ (void)resume NS_UNAVAILABLE;
/**
 Release any loaded resiurces, that depended in sdk work.
 @warning SDK work can recover only in next app session
 */
+ (void)stop NS_UNAVAILABLE;
/**
 Unavailable method
 */
+ (void)deinitialize NS_UNAVAILABLE;
@end
/**
 Set user metadata for relevant ad targeting
 */
@interface Appodeal (UserMetadata)
/**
 User ID setter
 @note Objective-C
 <pre> [Appodeal setUserId:@"USER_ID"]; </pre>
 @note Swift
 <pre> Appodeal.setUserId("USER_ID") </pre>
 @param userId Set userId as string
 */
+ (void)setUserId:(nonnull NSString *)userId;
/**
 User ID getter
 @note Objective-C
 <pre> [Appodeal userId]; </pre>
 @note Swift
 <pre> Appodeal.userId() </pre>
 */
+ (nullable NSString *)userId;
@end
