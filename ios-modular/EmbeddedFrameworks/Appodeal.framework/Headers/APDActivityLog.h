//
//  APDActivityLog.h
//  Appodeal
//
//  Created by Stas Kochkin on 21.05.2023.
//  Copyright © 2023 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Appodeal/APDDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, APDActivityType) {
    APDActivityTypeMediationStart = 0,
    APDActivityTypeMediationFinish,
    APDActivityTypeImpressionStart,
    APDActivityTypeImpressionFinish,
    APDActivityTypeClick
};
/// Class that return information about mediation activity
@interface APDActivityLog : NSObject <NSCopying>
/// Type of activity
@property (nonatomic, assign, readonly) APDActivityType activityType;
/// Ad type
@property (nonatomic, assign, readonly) APDAdType adType;
/// Ad network name
@property (nonatomic, copy, readonly) NSString *adNetwork;
/// Custom message
@property (nonatomic, copy, readonly, nullable) NSString *message;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
