//
//  STKMeasureEventProtocol.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 19.08.2020.
//  Copyright © 2020 Appodeal. All rights reserved.
//

#import <StackOpenMeasure/STKMeasureViewContextProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@protocol STKMeasureEventProtocol <NSObject>

- (void)didLoad;

- (void)didImpression;

@end

@protocol STKMeasureMediaEventProtocol <NSObject>

- (void)startWithPlayerVolume:(CGFloat)playerVolume duration:(CGFloat)duration;

- (void)firstQuartile;

- (void)midpoint;

- (void)thirdQuartile;

- (void)complete;

- (void)pause;

- (void)resume;

- (void)skipped;

- (void)volumeChangeTo:(CGFloat)playerVolume;

- (void)playerStateChangeToNormal;

- (void)playerStateChangeToFullscreen;

- (void)adUserInteraction;

@end

NS_ASSUME_NONNULL_END
