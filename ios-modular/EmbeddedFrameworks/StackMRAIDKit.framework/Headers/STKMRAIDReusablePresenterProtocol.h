//
//  AMKPresenterReusableProtocol.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackMRAIDKit/STKMRAIDAd.h>


NS_ASSUME_NONNULL_BEGIN

@protocol STKMRAIDReusablePresenter;

@protocol STKMRAIDReusablePresenterDelegate <NSObject>

@optional

- (void)presenter:(id<STKMRAIDReusablePresenter>)presenter didReuseAd:(STKMRAIDAd *)ad;

@end

@protocol STKMRAIDReusablePresenter <NSObject>

@property (nonatomic, weak) id<STKMRAIDReusablePresenterDelegate> reusableDelegate;

- (void)presenterReuseAd:(STKMRAIDAd *)ad;

@end

NS_ASSUME_NONNULL_END
