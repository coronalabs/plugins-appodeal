//
//  UIImageView+STKUIKit.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImageView (STKUIKit)

@property (class, nonatomic, readonly) UIImageView *(^stkFastImageCache)(NSURL *_Nullable);
@property (class, nonatomic, readonly) UIImageView *(^stkPlaceholderFastImageCache)(NSURL *_Nullable, UIImage *_Nullable);
@property (class, nonatomic, readonly) UIImageView *(^stkFastBitmap)(const void *_Nullable bytes, int length);

@property (nonatomic, readonly) void(^stkFastImageCache)(NSURL *_Nullable);
@property (nonatomic, readonly) void(^stkPlaceholderFastImageCache)(NSURL *_Nullable, UIImage *_Nullable);

@end

NS_ASSUME_NONNULL_END
