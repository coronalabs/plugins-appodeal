//
//  STKUIDefines.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKUIDefines : NSObject

@property (class, nonatomic, readonly) UIColor *strokeColor;

@property (class, nonatomic, readonly) UIColor *fillColor;

@property (class, nonatomic, readonly) UIColor *mainColor;

@property (class, nonatomic, readonly) CGFloat controlSize; // 40f

@property (class, nonatomic, readonly) UIEdgeInsets contentInset; // {5, 5, 5, 5}}

@end

NS_ASSUME_NONNULL_END
