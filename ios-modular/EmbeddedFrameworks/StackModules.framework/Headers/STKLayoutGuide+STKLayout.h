//
//  STKLayoutGuide+STKLayout.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import "STKLayoutGuide.h"

NS_ASSUME_NONNULL_BEGIN

@interface STKLayoutGuide (STKLayout)

@property (nonatomic, readonly) STKLayoutGuide *left;
@property (nonatomic, readonly) STKLayoutGuide *right;
@property (nonatomic, readonly) STKLayoutGuide *top;
@property (nonatomic, readonly) STKLayoutGuide *bottom;
@property (nonatomic, readonly) STKLayoutGuide *leading;
@property (nonatomic, readonly) STKLayoutGuide *trailing;
@property (nonatomic, readonly) STKLayoutGuide *width;
@property (nonatomic, readonly) STKLayoutGuide *height;
@property (nonatomic, readonly) STKLayoutGuide *centerX;
@property (nonatomic, readonly) STKLayoutGuide *centerY;
@property (nonatomic, readonly) STKLayoutGuide *lastBaseline;
@property (nonatomic, readonly) STKLayoutGuide *firstBaseline;

@end

NS_ASSUME_NONNULL_END
