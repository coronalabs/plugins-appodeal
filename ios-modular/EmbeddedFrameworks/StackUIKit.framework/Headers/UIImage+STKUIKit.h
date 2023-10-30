//
//  UIImage+STKUIKit.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (STKUIKit)

@property (class, nonatomic, copy, readonly) CGImageRef _Nullable(^imageRef)(NSData *_Nullable data, int size);
@property (class, nonatomic, readonly) UIImage *_Nullable(^stkBitmap)(const void *_Nullable bytes, int length);

@end

NS_ASSUME_NONNULL_END
