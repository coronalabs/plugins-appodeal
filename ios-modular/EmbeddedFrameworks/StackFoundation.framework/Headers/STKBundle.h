//
//  STKBundle.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKBundle : NSObject

@property (class, nonatomic, readonly) NSString *ID;

@property (class, nonatomic, readonly) NSString *bundleVersion;

@property (class, nonatomic, readonly) NSArray <NSString *> *registeredSKAdNetworkIdentifiers;

@end

NS_ASSUME_NONNULL_END
