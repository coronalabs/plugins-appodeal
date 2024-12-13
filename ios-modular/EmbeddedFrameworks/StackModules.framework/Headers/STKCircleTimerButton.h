//
//  STKCircleTimerButton.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKCoreButton.h>

@interface STKCircleTimerButton : UIView

@property (nonatomic, readonly) STKCoreButtonSettingsBuilder *builder;

+ (STKCircleTimerButton *)timerWithTimeInterval:(NSTimeInterval)interval
                                     completion:(void(^)(STKCircleTimerButton *))completion;

- (void)fire;

@end
