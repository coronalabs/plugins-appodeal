//
//  STKRotationController.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKRotationController : UIViewController

@property (nonatomic, assign) UIInterfaceOrientation estimatePreferredOrientation;

@property (nonatomic, assign) BOOL estimateShouldAutorotate;

- (void)presentFromViewController:(UIViewController *)viewController animated:(BOOL)flag completion:(void (^)(void))completion;

@end

NS_ASSUME_NONNULL_END
