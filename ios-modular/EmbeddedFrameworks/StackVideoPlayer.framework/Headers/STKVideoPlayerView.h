//
//  STKVideoPlayerView.h
//  StackVideoPlayer
//
//  Created by Ilia Lozhkin on 1/9/19.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, AVPVideoEvent) {
    AVPVideoEventStart = 0,
    AVPVideoEventFirstQurtile,
    AVPVideoEventMidpoint,
    AVPVideoEventThirdQurtile,
    AVPVideoEventFinish,
    AVPVideoEventClick,
    AVPVideoEventPause,
    AVPVideoEventResume,
    AVPVideoEventStartBuffering,
    AVPVideoEventFinishBuffering
};

@class STKVideoPlayerView;

@protocol STKVideoPlayerViewDelegate <NSObject>

- (void)playerViewReady:(STKVideoPlayerView *)playerView;
- (void)playerView:(STKVideoPlayerView *)playerView didFailWithError:(NSError *)error;
- (void)playerView:(STKVideoPlayerView *)playerView sendEvent:(AVPVideoEvent)event;
- (void)playerView:(STKVideoPlayerView *)playerView didUpdateProgress:(CGFloat)progress;

@end

@interface STKVideoPlayerView : UIView
/**
 Can set mute on/off for player
 */
@property (nonatomic, assign) BOOL mute;
/**
 Check time controll status
 */
@property (nonatomic, assign, readonly, getter=isTimeControlStatusPlaying) BOOL timeControlStatusPlaying;
/**
 Set player delegate
 */
@property (nonatomic,   weak) id<STKVideoPlayerViewDelegate> delegate;
/**
 Copy instance of progress bar
 */
@property (nonatomic, readonly) UIView *progressView;

- (void)loadWithURL:(NSURL*)videoURL;
- (void)play;
- (void)pause;
- (void)resume;
- (void)stop;
- (void)repeat;
- (void)invalidate;
- (float)duration;
- (float)currentTime;
- (void)setShouldResumeWhenApplicatonBecomeActive:(BOOL)shouldResumeWhenApplicatonBecomeActive;
- (UIImage *)takeScreenshot;

@end
