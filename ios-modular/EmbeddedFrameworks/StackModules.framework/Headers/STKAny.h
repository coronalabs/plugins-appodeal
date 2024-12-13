//
//  STKAny.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class STKAny;

#define ANY(_obj) [STKAny any:_obj]

typedef _Nullable id (^STKAnyFlatMap)(id);
typedef void(^STKAnyReduce)(id, id);
typedef BOOL (^STKAnyFilter)(id);
typedef NSComparator STKAnySort;

@interface STKAny : NSObject

@property (nonatomic, readonly, nullable) id value;

@property (nonatomic, readonly) NSString *string;
@property (nonatomic, readonly) NSNumber *number;
@property (nonatomic, readonly) NSURL *url;
@property (nonatomic, readonly) NSArray *array;
@property (nonatomic, readonly) NSArray <NSURL *>*arrayOfURL;
@property (nonatomic, readonly) NSArray <NSString *>*arrayOfString;

@property (nonatomic, readonly) STKAny *(^from)(NSString *);
@property (nonatomic, readonly) STKAny *(^flatMap)(STKAnyFlatMap);
@property (nonatomic, readonly) STKAny *(^reduce)(id, STKAnyReduce);
@property (nonatomic, readonly) STKAny *(^filter)(STKAnyFilter);
@property (nonatomic, readonly) STKAny *(^sort)(STKAnySort);

+ (instancetype)any:(_Nullable id)object;

@end

NS_ASSUME_NONNULL_END
