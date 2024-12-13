//
//  STKConnection.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKNetworkReachability.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKConnection : NSObject

@property (class, nonatomic, readonly) STKNetworkStatus status;

@property (class, nonatomic, readonly) NSString *statusName;

@property (class, nonatomic, readonly) NSString *carrierName;

@property (class, nonatomic, readonly) NSString *mobileCountryCode;

@property (class, nonatomic, readonly) NSString *mobileNetworkCode;

@property (class, nonatomic, readonly, nullable) NSString *mccmnc;

@property (class, nonatomic, readonly, nullable) NSString *subtype;

@end

NS_ASSUME_NONNULL_END
