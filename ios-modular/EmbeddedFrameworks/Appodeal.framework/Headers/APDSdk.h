//
//  APDSdk.h
//  Appodeal
//
//  AppodealSDK version 3.2.0-beta.1
//
//  Copyright © 2023 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Appodeal/APDDefines.h>

#if __has_include(<StackConsentManager/StackConsentManager.h>)
#import <StackConsentManager/StackConsentManager.h>
#endif


typedef void(^APDAdRevenueHandler)(_Nonnull id<AppodealAdRevenue>);

/**
 Main SDK object, that managed network request, ad modules and statistics data.
 You should initialize the SDK before you start loading any ad types.
 You can do this in
 <pre> - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions </pre>
 for example.
 
 @note For example initialization code can be something like this:
 <pre>
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
 [[APDSdk sharedSdkWithApiKey: YOUR_API_KEY] initializeForAdTypes: APDAdTypeInterstitialAd];
 return YES;
 }
 </pre>
 
 After SDK initialization, you can get an instance of SDK by calling [APDSdk sharedSdk];
 You can additionally set other SDK settings before/after SDK initialization
 
 @warning You must call sharedSdkWithApiKey:(NSString *)apiKey firstly.
 */
@interface APDSdk : NSObject
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
 Set custom extra data for sdk
 */
@property (nonatomic, readonly, copy, nonnull) NSDictionary <NSString *, id> *extras;
/**
 You can set custom segments/placement filters by using this method.
 Configure rules for segments in <b>Appodeal Dashboard</b>.
 @note For example, if you want to create a segment of users who complete 20 or more levels,
 you create a rule in the dashboard with name "completedLevels" of type Int,
 operator GreaterThanOrEqualTo and value 10, now you implement following code:
 @note Objective-C
 <pre>
 NSDictionary *state = {
    @"completedLevels" : CURRENT_NUMBER_OF_COMPLETED_LEVELS
 };
 [[APDSdk sharedSdk] setCustomState:state];
 </pre>
 @note Swift
 <pre>
 APDSdk.sharedSdk().customState = ["completedLevels": CURRENT_NUMBER_OF_COMPLETED_LEVELS]
 </pre>
 And then CURRENT_NUMBER_OF_COMPLETED_LEVELS becomes 10 or greater
 Your segments settings become available
 */
@property (nonatomic, readonly, copy, nonnull) NSDictionary <NSString *, id> *customState;
/**
 Called when the ad is estimated to have earned revenue.
*/
@property (nonatomic, readwrite, copy, nullable) APDAdRevenueHandler adRevenueHandler;
/**
 Singleton instance of APDSdk
 @note Objective-C <pre> [APDSdk sharedSdkWithApiKey:@"API_KEY"]; </pre>
 @note Swift <pre> APDSdk.sharedSdkWithApiKey("API_KEY") </pre>
 @param apiKey String API key parameter from Appodeal Dashboard
 @return Singleton instance of APDSdk
 */
+ (instancetype _Nonnull)sharedSdkWithApiKey:(nonnull NSString *)apiKey;
/**
 Always returns same instance SDK returned by first call of
 @see <pre> +sharedSdkWithApiKey: </pre>
 @note Objective-C <pre> [APDSdk sharedSdk]; </pre>
 @note Swift <pre> APDSdk.sharedSdk() </pre>
 @return Instance of APDSdk
 */
+ (instancetype _Nonnull)sharedSdk;
/**
 Call this method to specify framework before initialization
 @note Objective-C <pre> [[APDSdk sharedSdk] setFramework:APDFrameworkNative version:@"5.1"]; </pre>
 @note Swift <pre> APDSdk.sharedSdk().setFramework(APDFramework.native, "5.1") </pre>
 @param framework Type of framework. Default is native iOS SDK
 @param version Framework version. Default nill
 */
- (void)setFramework:(APDFramework)framework version:(nullable NSString *)version;
/**
 Updates user consent in GDPR regulation
 @param userConsent User consent flag that indicates that user give consent on personal data processing
 */
- (void)updateUserConsentGDPR:(APDGDPRUserConsent)userConsent;
/**
 Updates user consent in CCPA regulation
 @param userConsent User consent flag that indicates that user give consent on personal data processing
 */
- (void)updateUserConsentCCPA:(APDCCPAUserConsent)userConsent;
/**
 Call this method to specify framework before initialization
 @param pluginVersion NSString version plugin
 */
- (void)setPluginVersion:(nonnull NSString *)pluginVersion;
/**
 Initialization of SDK for types
 @note Objective-C <pre> [[APDSdk sharedSdk] initializeForAdTypes:AppodealAdTypeInterstitial | AppodealAdTypeRewardedVideo]; </pre>
 @note Swift
 <pre>
 let adTypes: AppodealAdType = [.banner, .interstitial]
 APDSdk.sharedSdk().initializeForAdTypes(adTypes)
 </pre>
 @param adTypes APDAdTypeInterstitialAd, APDAdTypeBanner, APDAdTypeNativeAd, APDAdTypeRewardedVideo, APDAdTypeMREC
 */
- (void)initializeForAdTypes:(APDAdType)adTypes;
/**
 Check that SDK is initialized for ad type
 @note Objective-C <pre> [[APDSdk sharedSdk] isInitializedForAdType:AppodealAdTypeInterstitial]; </pre>
 @note Swift <pre> APDSdk.sharedSdk().isInitializedForAdType(APDAdType.interstitial) </pre>
 @param adType APDAdType value
 @return YES if SDK initialized for this type, or NO if not
 */
- (BOOL)isInitializedForAdType:(APDAdType)adType;
/**
 If you set YES to this method you get only
 test ad with 0$ eCPM
 @note Objective-C <pre> [[APDSdk sharedSdk] setTestingMode:YES]; </pre>
 @note Swift <pre> APDSdk.sharedSdk().setTesingMode(true) </pre>
 @warning use this method before initilized sdk
 @param enabled Boolean flag
 */
- (void)setTestingMode:(BOOL)enabled;
/**
 Appodeal SDK supports multiple log level for internal logging,
 and ONLY one (VERBOSE) log level for third party ad networks.
 To enable third party ad networks logging, set log level to APDLogLevelVerbose.
 If the log level is something other than APDLogLevelVerbose, all third party ad networks logging will be suppressed (if possible).
 @param logLevel APDLogLevel value
 */
+ (void)setLogLevel:(APDLogLevel)logLevel;
/**
 Disabling/enabling location tracking
 @param enabled Set to NO by default
 */
- (void)setLocationTracking:(BOOL)enabled;
/**
 Disabling/enabling child app
 @param childDirectedTreatment Set to NO by default
 */
- (void)setChildDirectedTreatment:(BOOL)childDirectedTreatment;
/**
 You can set custom rule by using this method. This method will override
 only custom state for specific state.
 Configure filters for segments/placements in <b>Appodeal Dashboard</b>.
 @note For example, you want to create a segment of users who complete 20 or more levels
 You create a rule in the dashboard with name "completedLevels" of type Int,
 operator GreaterThanOrEqualTo and value 10, and then you implement the following code:
 @note Objective-C
 <pre>
 [APDSdk.sharedSdk setCustomStateValue:CURRENT_NUMBER_OF_COMPLETED_LEVELS forKey:@"completedLevels"];
 </pre>
 @note Swift
 <pre>
 APDSdk.sharedSdk.setCustomStateValue(CURRENT_NUMBER_OF_COMPLETED_LEVELS, forKey:"completedLevels")
 </pre>
 Call this method any time you want, segments change dynamically
 @note And then CURRENT_NUMBER_OF_COMPLETED_LEVELS become 10 or greater
 Your segments settings become available
 @param value JSON encodable object. Might be nil
 @param key Nonnull string value
 */
- (void)setCustomStateValue:(nullable id)value forKey:(nonnull NSString *)key;
/**
 Set custom extra value for specific key
 @note Objective-C
 <pre> [APDSdk.sharedSdk setExtrasValue:@"bar" forKey:@"foo"]; </pre>
 @note Swift
 <pre> Appodeal.setExtrasValue("bar", forKey:"foo"]) </pre>
 @param value JSON encodable object. Might be nil
 @param key Nonnull string value
 */
- (void)setExtrasValue:(nullable id)value forKey:(nonnull NSString *)key;
/**
 User ID setter
 @note Objective-C
 <pre> [[APDSdk sharedSdk] setUserId:@"USER_ID"]; </pre>
 @note Swift
 <pre> APDSdk.shared().setUserId("USER_ID") </pre>
 @param userId Set userId as string
 */
- (void)setUserId:(nullable NSString *)userId;
/**
 Get framework type
 @note Objective-C
 <pre> [[APDSdk sharedSdk] framework]; </pre>
 @note Swift
 <pre> APDSdk.sharedSdk().framework() </pre>
 */
- (APDFramework)framework;
/**
 Get framework version
 @note Objective-C
 <pre> [[APDSdk sharedSdk] frameworkVersion]; </pre>
 @note Swift
 <pre> APDSdk.sharedSdk().frameworkVersion() </pre>
 */
- (nullable NSString *)frameworkVersion;
/**
 Get plugin version
 @note Objective-C
 <pre> [[APDSdk sharedSdk] pluginVersion]; </pre>
 @note Swift
 <pre> APDSdk.sharedSdk().pluginVersion() </pre>
 */
- (nullable NSString *)pluginVersion;
/**
 Get current user segment id
 @note Objective-C
 <pre> [[APDSdk sharedSdk] segmentId]; </pre>
 @note Swift
 <pre> APDSdk.sharedSdk().segmentId() </pre>
*/
- (nonnull NSNumber *)segmentId;
@end


@interface APDSdk (InAppPurchase)
/**
 In-app purchase tracking.
 Call this method after user makes an in-app purchase
 @param amount Amount of in-app purchase, for example @0.99
 @param currency In-app purchase currency, for example @"USD"
 */
- (void)trackInAppPurchase:(nonnull NSNumber *)amount currency:(nonnull NSString *)currency;
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
- (void)validateAndTrackInAppPurchase:(nullable NSString *)productId
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
- (void)trackEvent:(nonnull NSString *)event
  customParameters:(NSDictionary * _Nullable)customParameters;

@end

#if __has_include(<StackConsentManager/StackConsentManager.h>)
@interface APDSdk (ConsentManager)
/**
  User has update consent through Stack Consent Manager.
  @param consentReport Consent report object from Stack Consent Manager
*/
- (void)setConsentReport:(nonnull id<STKConsent>)consentReport;
@end
#endif
