//
//  STKVASTAssetAsset.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/13/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <StackIABAssets/StackIABAssets.h>
#import <StackVASTAssets/STKVASTAssetCompanion.h>
#import <StackVASTAssets/STKVASTAssetTrackProtocol.h>
#import <StackVASTAssets/STKVASTAssetPostbanner.h>
#import <StackVASTAssets/STKVASTAssetOMVerification.h>

NS_ASSUME_NONNULL_BEGIN

/// Asset
@interface STKVASTAsset : NSObject
/// Duration of video
/// By default is 0
@property (nonatomic, assign, readonly) NSTimeInterval duration;
/// Skipp offset of skippable video
/// By default is 0
@property (nonatomic, assign, readonly) NSTimeInterval skipOffset;
/// Video size
/// By default is {0, 0}
@property (nonatomic, assign, readonly) CGSize size;
/// Video vertical position
@property (nonatomic, assign, readonly) STKIABAssetVerticalPosition verticalPosition;
/// Video horizontal position
@property (nonatomic, assign, readonly) STKIABAssetHorizontalPosition horizontalPosition;
/// Background color
@property (nonatomic, copy, readonly) UIColor *backgroundColor;
/// Fullscreen
@property (nonatomic, assign, readonly) BOOL fullscreen;
/// Enables user click by video
/// By default is NO
@property (nonatomic, assign, readonly) BOOL videoClickable;
/// disable video volume
/// By default is NO
@property (nonatomic, assign, readonly) BOOL videoMuted;
/// Opens product after user tap on closable view on video
/// By default is NO
@property (nonatomic, assign, readonly) BOOL r1;
/// Opens product after video did complete
/// By default is NO
@property (nonatomic, assign, readonly) BOOL r2;
/// Opens product after video did complete, or Opens product after user tap on closable view on video
/// By default is NO
@property (nonatomic, assign, readonly) BOOL r3;
/// Enables autorotate of video
/// By default is NO
@property (nonatomic, assign, readonly) BOOL autorotate;
/// Set policy to use safe area layout guide or not
@property (nonatomic, assign, readonly) BOOL ignoresSafeAreaLayoutGuide;
/// Video media file URL
@property (nonatomic, copy, readonly, nullable) NSURL *contentURL;
/// Tracker URL
@property (nonatomic, copy, readonly, nonnull) id<STKVASTAssetTrack> track;
/// Mute button guide
/// By default is positioning at the top left corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *muteAsset;
/// By default is positioning at the bottom right corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *CTAAsset;
/// Closable view countdown timer guide
/// By default is positioning at the top right corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *countdownAsset;
/// Closable view guide
/// By default is positioning at the top right corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *closableViewAsset;
/// Repeat button guide
/// By default is positioning at the bottom left corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *repeatViewAsset;
/// Progress bar guide
/// By default is positioning at the bottom center corner,
@property (nonatomic, copy, readonly, nonnull) STKIABAsset *progressAsset;
/// Indicates that player should present postbanner
/// By default is YES
@property (nonatomic, assign, readonly) BOOL companionEnabled;
/// Indicates that player should present BMSKOverlay
/// By default is NO
@property (nonatomic, assign, readonly) BOOL bmSKOverlayEnabled;
/// Indicates that player should present SKOverlay
/// By default is NO
@property (nonatomic, assign, readonly) BOOL skOverlayEnabled;
///Force orientation of Creative
@property (nonatomic, copy, readonly, nullable) NSString *forceOrientation;
/// Postbanners
@property (nonatomic, strong, readonly, nullable) NSArray <STKVASTAssetCompanion *> *companions;
/// In-stream companions
/// This companion use for banner
@property (nonatomic, strong, readonly, nullable) NSArray <STKVASTAssetCompanion *> *bannerCompanions;
/// Companions from ext companions
/// This companion use for CTA custom view
@property (nonatomic, strong, readonly, nullable) NSArray <STKVASTAssetCompanion *> *extCompanions;
/// Postbanner extension
@property (nonatomic, copy, readonly) STKVASTAssetPostbanner *postbanner;
/// OM verirfications
@property (nonatomic, strong, readonly, nullable) NSArray <STKVASTAssetOMVerification *> *verifications;
/// AD play position in AD Pod
@property (nonatomic, readonly, nullable) NSNumber *sequence;

@end

NS_ASSUME_NONNULL_END
