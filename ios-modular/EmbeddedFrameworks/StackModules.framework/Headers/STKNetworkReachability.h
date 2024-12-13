//
//  STKNetworkReachability.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, STKNetworkStatus) {
    STKNetworkStatusUndefined = -1,
    STKNetworkStatusNotReachability = 0,
    STKNetworkStatusWiFi = 1,
    STKNetworkStatusWWAN = 2
};

NS_ASSUME_NONNULL_BEGIN

@interface STKNetworkReachability : NSObject

@property (nonatomic, assign, readonly) STKNetworkStatus status;

@property (nonatomic, copy) void (^reachabilityChangeBlock)(void);

- (instancetype)initWithHost:(NSString *)host;

- (void)startMonitoring;

- (void)stopMonitoring;

@end

NS_ASSUME_NONNULL_END
