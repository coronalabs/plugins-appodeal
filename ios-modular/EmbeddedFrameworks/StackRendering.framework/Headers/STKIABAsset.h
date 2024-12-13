//
//  STKVASTAssetAssetExtension.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/14/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StackRendering/STKIABAssetsDefines.h>

@protocol STKIABViewProtocol;

NS_ASSUME_NONNULL_BEGIN
/// Control guide
@interface STKIABAsset : NSObject <NSCopying>
/// Style of control
@property (nonatomic, readonly) NSString *style;
/// Control guide enable value. By default isNO
@property (nonatomic, readonly) BOOL visible;
/// Stroke Color value. By default isUIColor.whiteColor
@property (nonatomic, readonly) UIColor *strokeColor;
/// Fill Color value. By default isUIColor.clearColor
@property (nonatomic, readonly) UIColor *fillColor;
/// Shadow color. By default is UIColor.black
@property (nonatomic, readonly) UIColor *shadowColor;
/// Hide after interval. By default is 2
@property (nonatomic, readonly) NSTimeInterval hideAfter;
/// Opacity. By default is 1
@property (nonatomic, readonly) CGFloat opacity;
/// Horizontal position
@property (nonatomic, readonly) STKIABAssetHorizontalPosition horizontalPostion;
/// Vertical position
@property (nonatomic, readonly) STKIABAssetVerticalPosition verticalPostion;
/// Asset size
@property (nonatomic, readonly) CGSize size;
/// Asset padding
@property (nonatomic, readonly) UIEdgeInsets insets;
/// Asset margins
@property (nonatomic, readonly) UIEdgeInsets margin;
/// Border
@property (nonatomic, readonly) BOOL outlined;
/// Stroke width
@property (nonatomic, readonly) CGFloat strokeWidth;
/// Font
@property (nonatomic, readonly) UIFont *font;

- (void)fillView:(UIView<STKIABViewProtocol> *)view;
@end
/// Extesnions
@interface STKIABAsset (Extension)
/// Any value
@property (nonatomic, readonly, nullable) id content;
@end

NS_ASSUME_NONNULL_END
