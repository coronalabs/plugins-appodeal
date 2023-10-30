//
//  UIViewController+STKUIKit.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIViewController (STKUIKit)

@property (class, nonatomic, readonly, nullable) UIViewController *stk_topPresentedViewController;
@property (class, nonatomic, readonly) UIViewController *stk_actualController;

@end

NS_ASSUME_NONNULL_END
