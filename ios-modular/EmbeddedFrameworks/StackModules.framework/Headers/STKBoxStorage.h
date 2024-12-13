//
//  STKBoxStorage.h
//
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class STKBoxStorage;

STKBoxStorage *STKBlackBox(void);

@interface STKBoxStorage: NSObject

@property (nonatomic, readonly) void(^append)(id);

@property (nonatomic, readonly) void(^remove)(NSUInteger);

@property (nonatomic, readonly) _Nullable id(^object)(NSUInteger);

@property (nonatomic, readonly) void(^clean)(void);

@end

NS_ASSUME_NONNULL_END
