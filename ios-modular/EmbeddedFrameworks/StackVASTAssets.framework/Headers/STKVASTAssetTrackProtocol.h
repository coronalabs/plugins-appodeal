//
//  STKVASTAssetTrackProtocol.h
//  StackVASTAssets
//
//  Created by Stas Kochkin on 28/01/2019.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSUInteger, STKVASTAssetEvent) {
    STKVASTAssetEventUndefined = 0,
    STKVASTAssetEventFirstQuartile,
    STKVASTAssetEventMidpoint,
    STKVASTAssetEventThirdQuartile,
    STKVASTAssetEventComplete,
    STKVASTAssetEventMute,
    STKVASTAssetEventUnmute,
    STKVASTAssetEventPause,
    STKVASTAssetEventResume,
    STKVASTAssetEventFullscreen,
    STKVASTAssetEventClose,
    STKVASTAssetEventStart,
    STKVASTAssetEventCreativeView,
    STKVASTAssetEventSkipp,
    STKVASTAssetEventExpand,
    STKVASTAssetEventCollapse,
    STKVASTAssetEventRewind,
    STKVASTAssetEventInvitation
};

NS_ASSUME_NONNULL_BEGIN


@protocol STKVASTAssetEventTracker <NSCopying>

@property (nonatomic, assign, readonly) STKVASTAssetEvent event;
@property (nonatomic, copy, readonly) NSArray <NSString *> *urls;

@end


@protocol STKVASTAssetTrack <NSCopying>

@property (nonatomic, copy, readonly, nullable) NSArray <NSString *> *clicksThrough;
@property (nonatomic, copy, readonly, nullable) NSArray <NSString *> *clicksTracking;
@property (nonatomic, copy, readonly, nullable) NSArray <NSString *> *impressionTracking;
@property (nonatomic, copy, readonly, nullable) NSArray <NSString *> *errorTracking;
@property (nonatomic, copy, readonly, nullable) NSArray <id<STKVASTAssetEventTracker>> *trackingEvents;

@end

NS_ASSUME_NONNULL_END
