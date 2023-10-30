//
//  NSArray+STKFoundation.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSArray <__covariant ObjectType> (STKFoundation)

typedef _Nullable id (^STKTransform)(ObjectType, NSUInteger);

typedef BOOL (^STKFilter)(ObjectType);

- (NSArray *)stk_transform:(STKTransform)transformation;

- (NSArray *)stk_concat;

+ (NSArray *)stk_concat:(NSArray *)arr, ... NS_REQUIRES_NIL_TERMINATION;

- (NSArray <ObjectType> *)stk_filter:(STKFilter)filter;

- (NSArray <ObjectType> *)stk_intersectArray:(NSArray <ObjectType> *)array;

- (NSArray <ObjectType> *)stk_arrayByRemovingObject:(ObjectType)object;

- (NSArray <ObjectType> *)stk_arrayByReplacingObject:(ObjectType)object withObject:(ObjectType)newObject;

@end

@interface NSMutableArray (STKFoundation)

- (void)stk_addObject:(nullable id)object;

@end

NS_ASSUME_NONNULL_END
