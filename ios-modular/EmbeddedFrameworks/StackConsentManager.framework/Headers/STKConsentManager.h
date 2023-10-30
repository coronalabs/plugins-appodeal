//
//  STKConsentDialog.h
//  StackConsentManager
//
//  Created by Stas Kochkin on 04.12.2019.
//  Copyright © 2019 com.stasko. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <StackConsentManager/STKVendorBuilder.h>


NS_ASSUME_NONNULL_BEGIN
@class STKConsentManager;

FOUNDATION_EXPORT NSString *const kSTKConsentManagerVersion;
/// Enumeration of consent manager error codes
/// - STKConsentManagerErrorUnknown: Unwknown
/// - STKConsentManagerErrorInternal: Internal SDK errors
/// - STKConsentManagerErrorNetworking: Errors dependened with network
/// - STKConsentManagerErrorInconsistent: Erros of inconsistent API calls
typedef NS_ENUM(NSInteger, STKConsentManagerError) {
    STKConsentManagerErrorUnknown = 0,
    STKConsentManagerErrorInternal,
    STKConsentManagerErrorNetworking,
    STKConsentManagerErrorInconsistent
};
/// Enumeration of result
/// - STKConsentBoolUnknown: Unwknown
/// - STKConsentBoolTrue: True
/// - STKConsentBoolFalse: False
typedef NS_ENUM(NSInteger, STKConsentBool) {
    STKConsentBoolUnknown = 0,
    STKConsentBoolTrue,
    STKConsentBoolFalse,
};
/// Enumeration of regulations
/// - STKConsentDialogRegulationNone: User not under any regulations. Consent dialog does not required
/// - STKConsentDialogRegulationGDPR: User under GDPR regulation. Consent dialog does is required
/// - STKConsentDialogRegulationCCPA: User under CCPA regulation. Consent dialog does is required
typedef NS_ENUM(NSInteger, STKConsentRegulation) {
    STKConsentRegulationUnknown = 0,
    STKConsentRegulationNone,
    STKConsentRegulationGDPR,
    STKConsentRegulationCCPA
};
/// Enumeration of consent result
/// - STKConsentStatusUnknown: User not gives any consent
/// - STKConsentStatusNonPersonalized: User denied consent
/// - STKConsentStatusPartlyPersonalized: User gives consent foi specific puproses and vendors
/// - STKConsentStatusPersonalized: User gives grant consent
typedef NS_ENUM(NSInteger, STKConsentStatus) {
    STKConsentStatusUnknown = 0,
    STKConsentStatusNonPersonalized,
    STKConsentStatusPartlyPersonalized,
    STKConsentStatusPersonalized
};
/// Enumeration of traking authorization status
/// - STKTrackingAuthorizationStatusNotDetermined: User not gives any consent. For devices with iOS 14.0 and higher
/// - STKTrackingAuthorizationStatusRestricted: User disable tracking permission alerts. For devices with iOS 14.0 and higher
/// - STKTrackingAuthorizationStatusDenied: User didn't give tracking permission or LAT is enabled in older iOS versions.
/// - STKTrackingAuthorizationStatusAuthorized: User gave tracking permission or LAT is diabled in older iOS versions.
typedef NS_ENUM(NSUInteger, STKTrackingAuthorizationStatus) {
    STKTrackingAuthorizationStatusNotDetermined = 0,
    STKTrackingAuthorizationStatusRestricted,
    STKTrackingAuthorizationStatusDenied,
    STKTrackingAuthorizationStatusAuthorized
};
/// Enumeration of dialog storage parameters
/// - STKConsentDialogStorageNone: Consent dialog will not modifies NSUserDefualts
/// - STKConsentDialogStorageUserDefaults: Consent dialog will rewrites NSUserDefualts
typedef NS_ENUM(NSInteger, STKConsentDialogStorage) {
    STKConsentDialogStorageNone = 0,
    STKConsentDialogStorageUserDefaults,
};
/// Consent protocol
@protocol STKConsent <NSObject>
@end
/// Display delegate
@protocol STKConsentManagerDisplayDelegate <NSObject>
/// Consent manager will present fullscreen dialog
/// @param consentManager Consent manager
- (void)consentManagerWillShowDialog:(STKConsentManager *)consentManager;
/// Consent manager failed while trying to present screen
/// @param consentManager Consent manager
/// @param error Error object
- (void)consentManager:(STKConsentManager *)consentManager didFailToPresent:(NSError *)error;
/// Consent manager did dismiss fullscreen dialog
/// @param consentManager Consent manager
- (void)consentManagerDidDismissDialog:(STKConsentManager *)consentManager;
@end
/// Consent dialog object used to provide
/// consent dialog for user under GDPR or CCPA regulations
@interface STKConsentManager : NSObject
/// Completion of loading consent dialog window callback
/// @param error Error object indicates that loading fails
typedef void(^STKConsentManagerCompletion)(NSError * _Nullable error);
/// Save consent information in iAB format in NSUserDefaults
/// By defualt this feature is disabled
/// - seealso:
/// [GDPR-Transparency-and-Consent-Framework]
/// (https://github.com/InteractiveAdvertisingBureau/GDPR-Transparency-and-Consent-Framework/)
@property (nonatomic, assign) STKConsentDialogStorage storage;
/// Identifies that consent Privacy Policy alert should be presented
@property (nonatomic, assign, readwrite) BOOL shouldShowConsentAlert;
/// Identifies that consent dialog should be presented
@property (nonatomic, assign, readonly) STKConsentBool shouldShowConsentDialog;
/// Identifies that consent dialog should be presented
@property (nonatomic, assign, readonly, getter=isConsentDialogReady) BOOL consentDialogReady;
/// Identifies that consent dialog is presented on screen
@property (nonatomic, assign, readonly, getter=isConsentDialogPresenting) BOOL consentDialogPresenting;
/// Return regulation type. None before synchronize method was called
@property (nonatomic, assign, readonly) STKConsentRegulation regulation;
/// Return consent status of user. Unknown before synchronize method was called
@property (nonatomic, assign, readonly) STKConsentStatus consentStatus;
/// User tracking authorization status
@property (nonatomic, assign, readonly) STKTrackingAuthorizationStatus trackingAuthorizationStatus;
/// Consent object used in Appodeal SDK
@property (nonatomic, readonly, copy, nullable) id<STKConsent> consent;
/// Consent string in iAB format
/// - seealso:
/// [GDPR-Transparency-and-Consent-Framework]
/// (https://github.com/InteractiveAdvertisingBureau/GDPR-Transparency-and-Consent-Framework/)
@property (nonatomic, copy, readonly, nullable) NSString *iabConsentString;
/// CCPA Opt-Out string in iAB format
/// - seealso:
/// [U.S. Privacy String]
/// (https://iabtechlab.com/wp-content/uploads/2019/11/U.S.-Privacy-String-v1.0-IAB-Tech-Lab.pdf)
@property (nonatomic, copy, readonly, nullable) NSString *iabUSPrivacyString;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
/// Nullable accessor of consent dialog
/// +sharedDialogWithAppKey should be called first
+ (instancetype)sharedManager;
/// Setup third party provided consent status
/// @param status User defined consent
/// @param regulation Regulation zone identifier
- (void)updateConsentStatus:(STKConsentStatus)status forRegulation:(STKConsentRegulation)regulation;
/// Provide custom vendors for consent dialog
/// Mehtod should be called before synchronise
/// @param vendorBuild Vendor builder block
- (void)registerCustomVendor:(void(^)(STKVendorBuilder *builder))vendorBuild;
/// Determines regulation policy
/// @param appKey Appodeal app key
/// @param completion Callback on synchronisation completion
- (void)synchronizeWithAppKey:(NSString *)appKey
                   completion:(nullable STKConsentManagerCompletion)completion;
/// Determines regulation policy
/// @param appKey Appodeal app key
/// @param customParameters Custom parameters
/// @param completion Callback on synchronisation completion
- (void)synchronizeWithAppKey:(NSString *)appKey
             customParameters:(NSDictionary <NSString *, id> *)customParameters
                   completion:(nullable STKConsentManagerCompletion)completion;
/// Prepare consent dialog window for presnetation
/// @param completion Callback on loading completion
- (void)loadConsentDialog:(nullable STKConsentManagerCompletion)completion;
/// Present consent dialog window
/// @param rootViewController Root view controller to present window
/// @param delegate Display delegate
- (void)showConsentDialogFromRootViewController:(UIViewController *)rootViewController
                                       delegate:(nullable id<STKConsentManagerDisplayDelegate>)delegate;
/// Return determined consent for vendor
/// @param vendorBundle Vendor name registered in Appodeal
- (STKConsentBool)hasConsentForVendorBundle:(NSString *)vendorBundle;
/// Prevent consent manager to ask app tracking transparency permissions
- (void)disableAppTrackingTransparencyRequest;
@end
NS_ASSUME_NONNULL_END
