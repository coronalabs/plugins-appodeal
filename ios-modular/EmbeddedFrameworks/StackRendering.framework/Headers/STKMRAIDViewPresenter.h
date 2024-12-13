//
//  AMKViewPresenter.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackRendering/STKMRAIDPresenterProtocol.h>
#import <StackRendering/STKMRAIDReusablePresenterProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDViewPresenter : UIView <STKMRAIDPresenter, STKMRAIDReusablePresenter>

@property (nonatomic, weak) id<STKMRAIDViewPresenterDelegate> delegate;
@property (nonatomic, weak) id<STKMRAIDReusablePresenterDelegate> reusableDelegate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
