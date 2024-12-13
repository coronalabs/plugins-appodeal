//
//  STKLayoutDimension.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLayoutDimension : NSObject

@property (nonatomic, assign) NSLayoutAttribute attribute;

@property (nonatomic, assign) NSLayoutRelation relation;

@property (nonatomic, assign) float offset;

@property (nonatomic, assign) float multiplier;

@end

NS_ASSUME_NONNULL_END
