//
//  STKVideoPlayerView.h
//

#import <UIKit/UIKit.h>

@class STKVideoPlayer;

@protocol STKVideoPlayerDelegate <NSObject>

- (void)playerReady:(STKVideoPlayer *)player;
- (void)playerDidStart:(STKVideoPlayer *)player;
- (void)playerDidClick:(STKVideoPlayer *)player;
- (void)playerDidPause:(STKVideoPlayer *)player;
- (void)playerDidResume:(STKVideoPlayer *)player;
- (void)playerDidFinish:(STKVideoPlayer *)player;
- (void)player:(STKVideoPlayer *)player didFailWithError:(NSError *)error;
- (void)player:(STKVideoPlayer *)player processInterval:(NSTimeInterval)interval;

@optional
- (void)playerDidStartBuffering:(STKVideoPlayer *)player;
- (void)playerDidEndBuffering:(STKVideoPlayer *)player;

@end

@interface STKVideoPlayer : UIView
/**
 Video duration
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;
/**
 Take screenshot duration / 2
 */
@property (nonatomic, strong, readonly) UIImage *screenshot;
/**
 Check time controll status
 */
@property (nonatomic, assign, readonly, getter=isTimeControlStatusPlaying) BOOL timeControlStatusPlaying;
/**
 Video current time
 */
@property (nonatomic, assign) NSTimeInterval currentTime;
/**
 Video volume 0.0 - 1.0;
 */
@property (nonatomic, assign) CGFloat volume;
/**
 Video delegate
 */
@property (nonatomic, weak) id<STKVideoPlayerDelegate> delegate;

/**
 Start loading video and prepare file
 
 @param videoURL - URL can be local url or web url
 */
- (void)loadWithURL:(NSURL *)videoURL;
/**
 Start playing
 */
- (void)play;
/**
 Pause playing
 */
- (void)pause;
/**
 Resume playing
 */
- (void)resume;
/**
 Stop playing
 */
- (void)stop;
/**
 Invalidate player
 */
- (void)invalidate;

- (void)setShouldResumeWhenApplicatonBecomeActive:(BOOL)shouldResumeWhenApplicatonBecomeActive;

@end
