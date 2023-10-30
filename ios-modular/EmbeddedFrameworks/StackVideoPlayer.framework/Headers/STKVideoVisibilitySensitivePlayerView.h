//
//  AVPVisiblePlayerView.h
//  StackVideoPlayer
//
//  Created by Ilia Lozhkin on 1/9/19.
//

#import <StackVideoPlayer/STKVideoPlayerView.h>

@interface STKVideoVisibilitySensitivePlayerView : STKVideoPlayerView

- (void)setVisibilityMonitoringEnabled:(BOOL)enabled;

@end
