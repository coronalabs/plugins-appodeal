//
//  STKCoreButtonSettingsBuilder.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKCoreButtonSettings.h>

@interface STKCoreButtonSettingsBuilder : NSObject

@property (nonatomic, readonly) STKCoreButtonSettings *settings;

- (STKCoreButtonSettingsBuilder *(^)(UIColor *))appendFillColor;
- (STKCoreButtonSettingsBuilder *(^)(UIColor *))appendStrokeColor;
- (STKCoreButtonSettingsBuilder *(^)(UIColor *))appendBorderStrokeColor;
- (STKCoreButtonSettingsBuilder *(^)(CGSize))appendShadowSize;
- (STKCoreButtonSettingsBuilder *(^)(float))appendShadowStrong;
- (STKCoreButtonSettingsBuilder *(^)(BOOL))appendShadowHide;
- (STKCoreButtonSettingsBuilder *(^)(UIViewContentMode))appendContentMode;

@end
