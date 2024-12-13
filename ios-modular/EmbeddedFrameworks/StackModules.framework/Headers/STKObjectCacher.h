//
//  STKObjectCacher.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKObjectCacher : NSObject

+ (void)objectWithName:(NSString * _Nullable)name
            completion:(void (^)(id _Nullable, NSError * _Nullable)) completion;

+ (void)cacheObject:(id<NSCoding> _Nullable)object
           withName:(NSString * _Nullable)name
         completion:(void (^)(NSError * _Nullable)) completion;

+ (void)removeObjectWithName:(NSString * _Nullable)name
                  completion:(void (^)(NSError * _Nullable))completion;
@end

NS_ASSUME_NONNULL_END
