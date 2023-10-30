//
//  UIApplication+STKUIKit.h
//  StackUIKit
//
//  Created by Stas Kochkin on 02.05.2023.
//  Copyright © 2023 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIApplication (STKUIKit)

- (nullable UIWindow *)stk_keyWindow;
- (NSArray <UIWindow *> *)stk_windows;

@end

NS_ASSUME_NONNULL_END
