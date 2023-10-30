//
//  UIView+STKViewability.h
//  StackUIKit
//
//  Created by Stas Kochkin on 02.05.2023.
//  Copyright © 2023 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (STKViewability)

- (BOOL)stk_geometryNotNil;

- (NSArray <UIView *> *)stk_allViewsThatHeigherOnScreen;

- (CGFloat)stk_intersectsParentWindowPercentage;

- (BOOL)stk_isVisibleOnScreenWithPercentage:(CGFloat)percentageVisible
                           overlayDetection:(BOOL)overlayDetection
                      weakDeviceSupportMode:(BOOL)weakDeviceSupportMode;

@end

NS_ASSUME_NONNULL_END
