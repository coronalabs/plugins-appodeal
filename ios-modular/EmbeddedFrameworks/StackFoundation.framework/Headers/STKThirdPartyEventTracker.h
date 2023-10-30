//
//  STKThirdPartyEventTracker.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSArray <NSString *>* kSTKErrorCodeMask(void);

@interface STKThirdPartyEventTracker : NSObject

@property (nonatomic, strong) NSArray <NSString *>* macrosCodeMask;

+ (void)sendTrackingEvents:(NSArray *_Nullable)trackingEvents;
+ (void)sendTrackingEvent:(NSString *_Nullable)trackingEvent;

- (void)sendCode:(NSUInteger)code trackingEvent:(NSString *_Nullable)trackingEvent;
- (void)sendCode:(NSUInteger)code trackingEvents:(NSArray <NSString *>*_Nullable)trackingEvents;

@end

NS_ASSUME_NONNULL_END
