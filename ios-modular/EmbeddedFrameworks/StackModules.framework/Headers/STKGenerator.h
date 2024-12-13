//
//  STKGenerator.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKGenerator : NSObject

@property (nonatomic, copy, readonly) NSString *generated;
@property (nonatomic, copy, readonly) NSString *format;
@property (nonatomic, copy, nullable) NSString *salt;

- (instancetype)initWithDate:(NSDate *)date;

- (void)update;
- (void)reset;

@end

NS_ASSUME_NONNULL_END
