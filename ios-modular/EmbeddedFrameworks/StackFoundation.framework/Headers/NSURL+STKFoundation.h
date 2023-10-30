//
//  NSURL+STKFoundation.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (STKFoundation)

+ (nullable NSURL *)stk_url:(nullable NSString *)string;

- (BOOL)stk_isRemoteUrl;

- (BOOL)stk_isLocalUrl;

- (BOOL)stk_isITMS;

- (BOOL)stk_isDPLK;

- (BOOL)stk_canOpen;

- (NSNumber *_Nullable)stk_storeId;

@end

NS_ASSUME_NONNULL_END
