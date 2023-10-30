//
//  STKValueTransformer.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef id _Nullable(^STKTransformBlock)(id object);

@interface STKValueTransformer : NSValueTransformer

+ (instancetype)transformerWithBlock:(STKTransformBlock _Nullable)block
                     reversibleBlock:(STKTransformBlock _Nullable)reversibleBlock;

+ (instancetype)arrayTransfomerWithBlock:(STKTransformBlock _Nullable)block
                         reversibleBlock:(STKTransformBlock _Nullable)reversibleBlock;

+ (instancetype)transformerToModelClass:(Class)cls;

+ (instancetype)arrayTransformerToModelClass:(Class)cls;

@end

NS_ASSUME_NONNULL_END
