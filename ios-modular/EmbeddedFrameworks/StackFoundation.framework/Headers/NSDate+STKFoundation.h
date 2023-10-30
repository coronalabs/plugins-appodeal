//
//  NSDate+STKFoundation.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSDate (STKFoundation)
/// Return wall time since correspondong date in years
@property (class, nonatomic, readonly) NSNumber *_Nullable(^stk_yearFromDate)( NSDate *_Nullable);
/// Return time interval from string in format 00:00.00
@property (class, nonatomic, readonly) NSTimeInterval (^stk_timeIntervalFromString)(NSString *);
/// Return wall time since 1970 in milliseconds
@property (class, nonatomic, readonly) long long stk_currentTimeInMilliseconds;
/// Return wall time since 1970 in seconds
@property (class, nonatomic, readonly) NSUInteger stk_currentTimeInSeconds;
/// Return wall time since 1970 in hours
@property (class, nonatomic, readonly) NSUInteger stk_currentTimeInHour;
/// Return wall time since 1970 in days
@property (class, nonatomic, readonly) NSUInteger stk_currentTimeInDay;
/// Return time in seconds since last device boot
@property (class, nonatomic, readonly) NSUInteger stk_monotonicTimeInSeconds;
/// Return wall time since 1970 in milliseconds
@property (nonatomic, readonly) NSTimeInterval stk_timeIntervalSince1970InMilliseconds;
@end


@interface NSDateFormatter (STKFoundation)
/// Return string from date of fromat yyyy-MM-dd'T'HH:mm:ss.SSSZZ
@property (class, nonatomic, readonly) NSString *_Nullable(^stk_stringFromDate)(NSDate *_Nullable);
@end

NS_ASSUME_NONNULL_END
