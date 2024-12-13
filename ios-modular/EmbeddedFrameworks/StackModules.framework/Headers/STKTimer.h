//
//  STKTimer.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKTimer : NSObject

+ (instancetype)timerWithInterval:(NSTimeInterval)interval
                         periodic:(BOOL)periodic
                            block:(dispatch_block_t)block; // periodically runs block on main thread

+ (instancetype)timerWithInterval:(NSTimeInterval)interval
                           leeway:(NSTimeInterval)leeway
                         periodic:(BOOL)periodic
                            block:(dispatch_block_t)block;

+ (instancetype)periodicTimerWithBlock:(NSTimeInterval (^)(void))block;

- (void)cancel; 

@end

NS_ASSUME_NONNULL_END
