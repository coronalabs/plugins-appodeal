//
//  STKLayoutGuide.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackUIKit/STKLayoutDimension.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLayoutGuide : NSObject

@property (nonatomic, weak, nullable) UIView *owner;

@property (nonatomic, strong) STKLayoutDimension *dimension;

@property (nonatomic, readonly, nullable) NSLayoutAnchor *layoutAnchor;

@end

NS_ASSUME_NONNULL_END
