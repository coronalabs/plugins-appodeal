#import <StackMRAIDKit/STKMRAIDAd.h>
#import "STKMRAIDWrapperConfiguration.h"


NS_ASSUME_NONNULL_BEGIN

@protocol STKMRAIDWrapper;

@protocol STKMRAIDWrapperDelegate <NSObject>

@required

- (void)didLoadAd:(id<STKMRAIDWrapper>)wrapper;
- (void)didExpireAd:(id<STKMRAIDWrapper>)wrapper;
- (void)didFailToShowAd:(id<STKMRAIDWrapper>)wrapper withError:(NSError *)error;
- (void)didFailToLoadAd:(id<STKMRAIDWrapper>)wrapper withError:(NSError *)error;

- (nullable UIViewController *)rootViewController;

@optional

- (BOOL)wrapper:(id<STKMRAIDWrapper>)wrapper shouldProcessNavigationWithURL:(NSURL *)URL;
- (BOOL)wrapperShouldResize:(id<STKMRAIDWrapper>)wrapper toPosition:(CGRect)position;

- (void)mraidServiceDidReceiveLogMessage:(NSString *)message;

- (void)wrapperWillLeaveApplication:(id<STKMRAIDWrapper>)wrapper;
- (void)wrapperWillPresentProductScreen:(id<STKMRAIDWrapper>)wrapper;
- (void)wrapperDidDismissProductScreen:(id<STKMRAIDWrapper>)wrapper;

@end


@protocol STKMRAIDWrapper <NSObject>

- (void)loadHTML:(NSString *)HTML withConfiguration:(STKMRAIDWrapperConfiguration *)configuration;
- (void)loadFromURL:(NSURL *)URL withConfiguration:(STKMRAIDWrapperConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
