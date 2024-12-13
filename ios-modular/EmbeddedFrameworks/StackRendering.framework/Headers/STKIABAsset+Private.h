//
//  STKVASTAssetControl+Private.h
//  StackVASTAssets
//
//  Created by Ilia Lozhkin on 12/19/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <StackRendering/STKIABAsset.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKIABAsset (Private)

@property (nonatomic, readwrite, copy) NSString *style;
@property (nonatomic, readwrite, assign) BOOL visible;
@property (nonatomic, readwrite, copy) UIColor *strokeColor;
@property (nonatomic, readwrite, copy) UIColor *fillColor;
@property (nonatomic, readwrite, copy) UIColor *shadowColor;
@property (nonatomic, readwrite, assign) NSTimeInterval hideAfter;
@property (nonatomic, readwrite, assign) CGFloat opacity;
@property (nonatomic, readwrite, assign) STKIABAssetHorizontalPosition horizontalPostion;
@property (nonatomic, readwrite, assign) STKIABAssetVerticalPosition verticalPostion;
@property (nonatomic, readwrite, assign) CGSize size;
@property (nonatomic, readwrite, assign) UIEdgeInsets insets;
@property (nonatomic, readwrite, assign) UIEdgeInsets margin;
@property (nonatomic, readwrite, assign) BOOL outlined;
@property (nonatomic, readwrite, assign) CGFloat strokeWidth;
@property (nonatomic, readwrite, copy) UIFont *font;
@property (nonatomic, readwrite) id content;

@end

NS_ASSUME_NONNULL_END
