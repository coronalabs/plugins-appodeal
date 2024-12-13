//
//  STKIABAssetBuilder.h
//  StackVASTAssets
//
//  Created by Ilia Lozhkin on 12/19/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StackModules/StackModules.h>
#import <StackRendering/STKIABAssetsDefines.h>

@class STKIABAsset;


NS_ASSUME_NONNULL_BEGIN

@interface STKIABAssetBuilder : NSObject
/// Control guide builded value
- (STKIABAsset *)asset;
/// Extension value
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendContent)(id _Nullable);
/// Extension value
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendStyle)(NSString *);
/// Visibility
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendVisible)(BOOL);
/// Visibility
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendOpacity)(CGFloat);
/// Hide after
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendHideAfter)(NSTimeInterval);
/// Control guide set stroke value
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendStrokeColor)(UIColor *);
/// Set shadow color
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendShadowColor)(UIColor *);
/// Control guide set fill value
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendFillColor)(UIColor *);
/// Control guide vertical position
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendVerticalPosition)(STKIABAssetVerticalPosition);
/// Control guide horizontal position
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendHorizontalPosition)(STKIABAssetHorizontalPosition);
/// Asset size
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendSize)(CGSize);
/// Asset padding
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendInsets)(UIEdgeInsets);
/// Asset margins
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendMargin)(UIEdgeInsets);
/// Border
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendOutline)(BOOL);
/// Stroke width
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendStrokeWidth)(CGFloat);
/// Font
@property (nonatomic, readonly) STKIABAssetBuilder *(^appendFont)(UIFont *);

@end

NS_ASSUME_NONNULL_END
