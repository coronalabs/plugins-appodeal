//
//  STKOperation.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class STKOperation;

typedef void(^STKOperationBlock)(STKOperation *);

@interface STKOperation : NSOperation

@property (nonatomic, copy, nullable) STKOperationBlock executionBlock;

- (void)complete;

@end

@interface STKGroupOperation : STKOperation

@property (nonatomic, strong, readonly) dispatch_group_t group;

@end

NS_ASSUME_NONNULL_END
