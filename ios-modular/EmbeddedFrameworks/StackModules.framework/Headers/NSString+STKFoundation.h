//
//  NSString+STKFoundation.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (STKCrypto)

@property (nonatomic, readonly) NSString *stk_SHA1HEXUppercased;

@property (nonatomic, readonly) NSString *stk_SHA256HEXUppercased;

@property (nonatomic, readonly) NSString *stk_MD5HEXUppercased;

@property (nonatomic, readonly) NSData *stk_SHA256;

@property (nonatomic, readonly, nullable) NSString *stk_XORDecrypted;

@end

NS_ASSUME_NONNULL_END
