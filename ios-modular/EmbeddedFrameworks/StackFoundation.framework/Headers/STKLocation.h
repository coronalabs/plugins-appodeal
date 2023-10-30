//
//  STKLocation.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLocation : NSObject

@property (class, nonatomic, readonly) BOOL locationTrackingEnabled;

@property (class, nonatomic, readonly, nullable) CLLocation *location;

@property (class, nonatomic, readonly) NSInteger utc;

+ (void)startMonitoring;

+ (void)stopMonitoring;

@end

NS_ASSUME_NONNULL_END
