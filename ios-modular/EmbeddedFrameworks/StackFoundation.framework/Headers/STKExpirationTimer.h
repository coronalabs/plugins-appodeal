//
//  STKExpirationTimer.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKExpirationTimer <__covariant ObjectType>: NSObject

@property (nonatomic, assign, readonly) NSTimeInterval expirationInterval;

+ (nullable instancetype)expirationTimerWithExpirationTimeinterval:(NSTimeInterval)expirationTime
                                                    observableItem:(ObjectType _Nullable)observableItem
                                                            expire:(void(^)(ObjectType _Nullable observableItem))expire;

+ (nullable instancetype)expirationTimerWithExpirationTimeinterval:(NSTimeInterval)expirationTime
                                                            expire:(void(^)(void))expire;

- (void)fire;

@end

NS_ASSUME_NONNULL_END
