//
//  APDPurchase.h
//  Appodeal
//
//  Created by Stas Kochkin on 21.01.2025.
//  Copyright © 2025 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AppodealPurchaseProtocol.h"


NS_ASSUME_NONNULL_BEGIN

@interface APDPurchase : NSObject <NSCopying, AppodealPurchase>

- (instancetype)initWithType:(APDPurchaseType)purchaseType
                   productId:(NSString *)productId
                       price:(NSString *)price
                    currency:(NSString *)currency
               transactionId:(NSString *)transactionId
                   timestamp:(NSTimeInterval)timestamp
        additionalParameters:(NSDictionary <NSString *, id> *)additionalParameters;

@end

NS_ASSUME_NONNULL_END
