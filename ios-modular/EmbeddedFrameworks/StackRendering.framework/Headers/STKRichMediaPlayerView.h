//
//  STKRichMediaPlayerView.h
//  StackRichMedia
//
//  Created by Stas Kochkin on 22/01/2019.
//

#import <UIKit/UIKit.h>
#import <StackRendering/STKRichMediaAssetProtocol.h>


@class STKRichMediaPlayerView;

NS_ASSUME_NONNULL_BEGIN

@protocol STKRichMediaPlayerViewDelegate <NSObject>

- (void)playerViewWillPresentFullscreen:(STKRichMediaPlayerView *)playerView;
- (void)playerViewDidDissmissFullscreen:(STKRichMediaPlayerView *)playerView;
- (void)playerViewWillShowProduct:(STKRichMediaPlayerView *)playerView;
- (void)playerViewDidInteract:(STKRichMediaPlayerView *)playerView;

@end

@interface STKRichMediaPlayerView : UIView

@property (nonatomic, weak, nullable) id <STKRichMediaPlayerViewDelegate> delegate;
@property (nonatomic, weak, nullable) UIViewController *rootViewController;

+ (instancetype)playerWithPlayerAsset:(id<STKRichMediaAsset>)playerAsset __deprecated_msg("use: init");
- (void)play __deprecated_msg("use: playAsset:");
- (void)playAsset:(id<STKRichMediaAsset>)playerAsset;

@end

NS_ASSUME_NONNULL_END
