#import "STKMRAIDViewPresenter.h"
#import <StackMRAIDKit/STKMRAIDWrapperProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@class STKMRAIDBanner;

@protocol STKMRAIDBannerDelegate <STKMRAIDWrapperDelegate>

- (void)bannerDidShow:(STKMRAIDBanner *)banner;

@end

@interface STKMRAIDBanner : UIView <STKMRAIDWrapper>

@property (nonatomic, weak) id<STKMRAIDBannerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
