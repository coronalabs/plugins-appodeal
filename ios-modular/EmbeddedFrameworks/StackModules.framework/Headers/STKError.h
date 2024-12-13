//
//  STKError.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKError : NSError

+ (instancetype)errorWithCode:(NSUInteger)code;

+ (instancetype)errorWithDescription:(NSString *)description, ... NS_FORMAT_FUNCTION(1,2);

+ (instancetype)errorWithCode:(NSUInteger)code description:(NSString *)description, ... NS_FORMAT_FUNCTION(2,3);

@end

@interface STKError (STKErrorWrapper)

+ (instancetype)wrapError:(NSError *_Nullable)error withCode:(NSUInteger)code;

+ (instancetype)wrapError:(NSError *_Nullable)error withDescription:(NSString *)description, ... NS_FORMAT_FUNCTION(2,3);

+ (instancetype)wrapError:(NSError *)error withCode:(NSUInteger)code description:(NSString *)description, ... NS_FORMAT_FUNCTION(3,4);

@end

NS_ASSUME_NONNULL_END
