//
//  UIColor+STKUIKit.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (STKUIKit)

@property (class, nonatomic, readonly) UIColor *_Nullable(^stk_fromHex)(NSString *_Nullable);

@end

NS_ASSUME_NONNULL_END
