//
//  STKAd.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, STKAdAuthorizationStatus) {
    STKAdAuthorizationStatusNotDetermined = 0,
    STKAdAuthorizationStatusRestricted,
    STKAdAuthorizationStatusDenied,
    STKAdAuthorizationStatusAuthorized
} NS_SWIFT_NAME(STKAd.AuthorizationStatus);

@interface STKAd : NSObject

@property (class, nonatomic, readonly) BOOL advertisingTrackingEnabled;

@property (class, nonatomic, readonly) STKAdAuthorizationStatus trackingAuthorizationStatus;

@property (class, nonatomic, readonly) NSString *generatedAdvertisingIdentifier;

@property (class, nonatomic, readonly) NSString *generatedVendorIdentifier;

@property (class, nonatomic, readonly) NSString *vendorIdentifier;

@property (class, nonatomic, readonly, nullable) NSString *advertisingIdentifier;

@end

NS_ASSUME_NONNULL_END
