//
//  STKSpinnerScreen.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKSpinnerScreen : NSObject

@property (class, nonatomic, assign, readonly) BOOL isDisplayed;

+ (void)setBlurred:(BOOL)blurred;

+ (void)setRetentionDeleay:(NSTimeInterval)retentionDelay;

+ (void)show;

+ (void)hide;

@end

NS_ASSUME_NONNULL_END
