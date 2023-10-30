//
//  STKRichMediaAsset.h
//  StackRichMedia
//
//  Created by Stas Kochkin on 22/01/2019.
//

#import <Foundation/Foundation.h>
#import <StackVASTAssets/StackVASTAssets.h>
#import <StackIABAssets/StackIABAssets.h>


@protocol STKRichMediaAsset <NSObject>
/**
 Video media file URL
 */
@property (nonatomic, copy, readonly, nullable) NSURL *contentURL;
/**
 Placeholder image view
 */
@property (nonatomic, copy, readonly, nullable) NSURL *placeholderImageURL;
/**
 Video tracker
 */
@property (nonatomic, copy, readonly, nonnull) id<STKVASTAssetTrack> track;

@optional
/**
 Video duration
 Default value - 0;
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;
/**
 Skipp Offset from Skippable video
 Default value - 0
 */
@property (nonatomic, assign, readonly) NSTimeInterval skipOffset;
/**
 Mute guide
 Default position - TopLeft
 */
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *muteAsset;
/**
 ClickToAction guide
 Default position - BottomRight
 */
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *CTAAsset;
/**
 Close guide
 Default position - TopRight
 */
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *countdownAsset;
/**
 Repeat guide
 Default position - BottomLeft
 */
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *repeatViewAsset;
/**
 ProgressBar guide
 Default position - LeftBottomRight, height - 2
 */
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *progressAsset;

@end
