//
//  STKLayoutConstraint.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKLayoutGuide.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLayoutConstraint : NSObject

@property (nonatomic, readonly, nullable) NSLayoutConstraint *layoutConstraint;

- (instancetype)initWith:(STKLayoutGuide *)owner target:(STKLayoutGuide *_Nullable)target;

- (STKLayoutConstraint *)appendOwner:(UIView *)owner;

- (STKLayoutConstraint *)appendTarget:(UIView *_Nullable)target;

- (void)active:(BOOL)active;

@end

NS_ASSUME_NONNULL_END
