#import <StackMRAIDKit/STKMRAIDWrapperProtocol.h>
#import "STKMRAIDInterstitialPresenter.h"

NS_ASSUME_NONNULL_BEGIN

@class STKMRAIDInterstitial;

@protocol STKMRAIDInterstitialDelegate <STKMRAIDWrapperDelegate>

@required

- (void)interstitialDidImpression:(STKMRAIDInterstitial *)interstitial;

@optional

- (void)interstitialDidAppear:(STKMRAIDInterstitial *)interstitial;
- (void)interstitialDidDissapear:(STKMRAIDInterstitial *)interstitial;

@end

@interface STKMRAIDInterstitial : NSObject <STKMRAIDWrapper>

@property (nonatomic, weak) id<STKMRAIDInterstitialDelegate> delegate;

- (void)presentAd;

@end

NS_ASSUME_NONNULL_END
