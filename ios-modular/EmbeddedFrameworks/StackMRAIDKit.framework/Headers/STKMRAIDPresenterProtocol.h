//
//  AMKPresenterProtocol.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackMRAIDKit/STKMRAIDAd.h>
#import <StackMRAIDKit/STKMRAIDPresentationConfiguration.h>


NS_ASSUME_NONNULL_BEGIN

@protocol STKMRAIDPresenter;


@protocol STKMRAIDPresenterDelegate <NSObject>

- (nullable UIViewController *)presenterRootViewController;

@optional

- (void)presenterDidBecomeUnavailable:(id<STKMRAIDPresenter>)presenter withError:(NSError *)error;
- (void)presenterWillLeaveApplication:(id<STKMRAIDPresenter>)presenter;
- (void)presenterWillPresentProductScreen:(id<STKMRAIDPresenter>)presenter;
- (void)presenterDidDismissProductScreen:(id<STKMRAIDPresenter>)presenter;

@end


@protocol STKMRAIDViewPresenterDelegate <STKMRAIDPresenterDelegate>

@required

- (void)presenterDidShow:(id<STKMRAIDPresenter>)presenter;

@optional

- (BOOL)presenterShouldResize:(id<STKMRAIDPresenter>)presenter toPosition:(CGRect)position;

@end


@protocol STKMRAIDInterstitialPresenterDelegate <STKMRAIDPresenterDelegate>

@optional

- (void)presenterDidAppear:(id<STKMRAIDPresenter>)presenter;
- (void)presenterDidDisappear:(id<STKMRAIDPresenter>)presenter;
- (void)presenterFailToPresent:(id<STKMRAIDPresenter>)presenter withError:(NSError *)error;

@end


@protocol STKMRAIDModalPresenterDelegate <STKMRAIDViewPresenterDelegate, STKMRAIDInterstitialPresenterDelegate>
@end


@protocol STKMRAIDPresenter <NSObject>

@property (nonatomic, weak) id<STKMRAIDPresenterDelegate> delegate;

@property (nonatomic, copy, readonly) STKMRAIDPresentationConfiguration *configuration;

- (instancetype)initWithConfiguration:(STKMRAIDPresentationConfiguration *)configuration;

- (void)presentAd:(STKMRAIDAd *)ad;

- (void)setViewable:(BOOL)viewable;

- (void)ad:(STKMRAIDAd *)ad willNavigateToURL:(NSURL *)URL;
- (void)ad:(STKMRAIDAd *)ad didReceiveProductURL:(NSURL *)URL;

@end

NS_ASSUME_NONNULL_END
