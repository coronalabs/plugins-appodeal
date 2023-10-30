//
//  NSObject+STKFoundation.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (STKFoundation)

@property (class, nonatomic, readonly) BOOL(^stk_isValid)(_Nullable id);

- (nullable id)stk_valueForKeyPath:(NSString *)keyPath;

@end

NS_ASSUME_NONNULL_END
