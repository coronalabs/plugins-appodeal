//
//  STKLocationManager.h
//
//  Copyright © 2019 Stack. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLocationManager : NSObject

@property (class, nonatomic, readonly) BOOL locationTrackingEnabled;

@property (nonatomic, copy, readonly, nullable) CLLocation *location;

- (void)startMonitoring;

- (void)stopMonitoring;

@end

NS_ASSUME_NONNULL_END
