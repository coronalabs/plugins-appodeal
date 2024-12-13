//
//  STKCoreButtonSettings.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKCoreButtonSettings : NSObject

@property (nonatomic, readonly) UIColor *fillColor;
@property (nonatomic, readonly) UIColor *strokeColor;
@property (nonatomic, readonly) UIColor *borderStrokeColor;
@property (nonatomic, readonly) CGSize shadowSize;
@property (nonatomic, readonly) float shadowStrong;
@property (nonatomic, readonly) BOOL shadowHide;

@property (nonatomic, readonly) UIViewContentMode mode;

+ (STKCoreButtonSettings *)defaultSettings;

@end

NS_ASSUME_NONNULL_END
