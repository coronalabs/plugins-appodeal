//
//  NSFileManager+STKFoundation.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^STKFileManagerEnumeration)(NSString *name, NSString *path, NSDictionary<NSFileAttributeKey, id> *attributes);

@interface NSFileManager (STKFoundation)

@property (nonatomic, readonly) BOOL (^stk_containsFile)(NSString *path);

@property (nonatomic, readonly) BOOL (^stk_containsDirectory)(NSString *path);

@property (nonatomic, readonly) void (^stk_createDirectory)(NSString *path);

@property (nonatomic, readonly) void (^stk_setAttribute)(NSString *path, NSDictionary <NSString *, NSString *> *attributes);

@property (nonatomic, readonly) NSString *_Nullable(^stk_getAttribute)(NSString *path, NSString *key);

@property (nonatomic, readonly) void (^stk_enumerateDirectory)(NSString *name, STKFileManagerEnumeration);

@property (nonatomic, readonly) NSArray *(^stk_contentOfDirectory)(NSString *path);

@property (nonatomic, readonly) BOOL (^stk_removeFile)(NSString *path);

@property (nonatomic, readonly) BOOL (^stk_copy)(NSString *path1, NSString *path2);


@end

NS_ASSUME_NONNULL_END
