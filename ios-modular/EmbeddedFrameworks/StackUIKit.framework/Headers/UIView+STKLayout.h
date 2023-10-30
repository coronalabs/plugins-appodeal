//
//  UIView+STKLayout.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackUIKit/STKLayoutGuide.h>
#import <StackUIKit/STKLayoutBuilder.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^STKLayoutBuilderBlock)(STKLayoutBuilder *);

@interface UIView (STKLayout)

@property (nonatomic, readonly) void(^stk_build)(STKLayoutBuilderBlock);

@property (nonatomic, readonly) STKLayoutGuide *stk_left;

@property (nonatomic, readonly) STKLayoutGuide *stk_right;

@property (nonatomic, readonly) STKLayoutGuide *stk_top;

@property (nonatomic, readonly) STKLayoutGuide *stk_bottom;

@property (nonatomic, readonly) STKLayoutGuide *stk_leading;

@property (nonatomic, readonly) STKLayoutGuide *stk_trailing;

@property (nonatomic, readonly) STKLayoutGuide *stk_width;

@property (nonatomic, readonly) STKLayoutGuide *stk_height;

@property (nonatomic, readonly) STKLayoutGuide *stk_centerX;

@property (nonatomic, readonly) STKLayoutGuide *stk_centerY;

@property (nonatomic, readonly) STKLayoutGuide *stk_lastBaseline;

@property (nonatomic, readonly) STKLayoutGuide *stk_firstBaseline;

@property (nonatomic, readonly) STKLayoutGuide *stk_safeGuide;

@property (nonatomic, readonly) STKLayoutGuide *stk_guide;

@end

NS_ASSUME_NONNULL_END
