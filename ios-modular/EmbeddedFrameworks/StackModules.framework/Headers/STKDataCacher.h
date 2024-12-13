//
//  STKDataCacher.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKFile.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKDataCacher : NSObject

@property (class, nonatomic, readonly) void(^cacheURL)(NSURL *_Nullable, STKSucceededFileBlock _Nullable, STKFailureFileBlock _Nullable);
@property (class, nonatomic, readonly) void(^cacheURLs)(NSArray <NSURL*> *_Nullable, STKMultipleSucceededFileBlock _Nullable, STKFailureFileBlock _Nullable);
@property (class, nonatomic, readonly) BOOL(^isCached)(NSURL *_Nullable);

@property (nonatomic, readonly) void(^cacheURL)(NSURL *_Nullable, STKSucceededFileBlock _Nullable, STKFailureFileBlock _Nullable);

@end

NS_ASSUME_NONNULL_END
