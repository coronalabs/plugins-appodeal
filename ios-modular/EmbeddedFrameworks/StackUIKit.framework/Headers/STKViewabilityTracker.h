//
//  STKViewabilityTracker.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^STKViewabilityBlock)(void);

@interface STKViewabilityTracker : NSObject

@property (nonatomic, assign) CFTimeInterval viewabilityInterval;

@property (nonatomic, assign) CFTimeInterval impressionInterval;

@property (nonatomic, assign) CFTimeInterval viewabilityTimerInterval;

@property (nonatomic, assign) CGFloat viewabilityPercentage;

@property (nonatomic, assign) BOOL loggingEnabled;

@property (nonatomic, assign) BOOL overlayDetection;

- (instancetype)initWithWeakMode:(BOOL)weakMode;

- (void)startTracking:(UIView *)view
           impression:(STKViewabilityBlock _Nullable)impression
             viewable:(STKViewabilityBlock _Nullable)viewable;

- (void)startTracking:(UIView *)view
             subviews:(NSArray <UIView *>* _Nullable)subviews
           impression:(STKViewabilityBlock _Nullable)impression
             viewable:(STKViewabilityBlock _Nullable)viewable;

@end

NS_ASSUME_NONNULL_END
