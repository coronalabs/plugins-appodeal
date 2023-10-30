//
//  STKCoreButton+Private.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackUIKit/STKCoreButton+Private.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKCoreButton (Private)

- (instancetype)initWithBuilder:(STKCoreButtonSettingsBuilder *)builder;

- (void)drawShadowWithCurrentPath:(UIBezierPath *_Nullable)path;

@end

NS_ASSUME_NONNULL_END
