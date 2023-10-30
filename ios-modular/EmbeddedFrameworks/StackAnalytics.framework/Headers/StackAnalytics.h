//
//  StackAnalytics.h
//  StackAnalytics
//
//  Created by Stas Kochkin on 20.11.2020.
//

#import <Foundation/Foundation.h>
#import <StackAnalytics/STAConfiguration.h>


NS_ASSUME_NONNULL_BEGIN

//! Project version number for StackAnalytics.
FOUNDATION_EXPORT double StackAnalyticsVersionNumber;

//! Project version string for StackAnalytics.
FOUNDATION_EXPORT const unsigned char StackAnalyticsVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <StackAnalytics/PublicHeader.h>

typedef NSString *const STKAppEvent NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(StackAnalytics.Event);
typedef NSString *const STKAppEventLevel NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(StackAnalytics.Level);

FOUNDATION_EXPORT STKAppEvent STKAppEventAdMediation;
FOUNDATION_EXPORT STKAppEvent STKAppEventAdServices;
FOUNDATION_EXPORT STKAppEvent STKAppEventAdImpression;
FOUNDATION_EXPORT STKAppEvent STKAppEventAdSession;
FOUNDATION_EXPORT STKAppEvent STKAppEventAdApi;
FOUNDATION_EXPORT STKAppEvent STKAppEventAdSegments;
FOUNDATION_EXPORT STKAppEvent STKAppEventApp;

FOUNDATION_EXPORT STKAppEventLevel STKAppEventLevelInfo;
FOUNDATION_EXPORT STKAppEventLevel STKAppEventLevelWarning;
FOUNDATION_EXPORT STKAppEventLevel STKAppEventLevelError;
FOUNDATION_EXPORT STKAppEventLevel STKAppEventDebug;
FOUNDATION_EXPORT STKAppEventLevel STKAppEventLevelVerbose;
FOUNDATION_EXPORT STKAppEventLevel STKAppEventLevelNone;


NS_SWIFT_NAME(StackAnalytics)
@interface StackAnalytics: NSObject

@property (nonatomic, class, readonly) NSString *sdkVersion;
@property (nonatomic, copy) NSURL *baseURL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)sharedInstance;

- (void)activateWithConfiguration:(STAConfiguration *)configuration;
- (void)trackEvent:(STKAppEvent)event
           session:(NSString *)session
            uptime:(NSTimeInterval)uptime
             level:(STKAppEventLevel)level
           message:(NSString *)message;
- (void)clearStorage;
@end

NS_ASSUME_NONNULL_END
