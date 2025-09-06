//
//  AppodealPurchase.h
//  Appodeal
//
//  Created by Stas Kochkin on 29.09.2025.
//  Copyright © 2025 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Appodeal/APDDefines.h>


NS_ASSUME_NONNULL_BEGIN

@protocol AppodealPurchase <NSObject>

@property (nonatomic, assign, readonly) APDPurchaseType purchaseType;
@property (nonatomic, copy, readonly, nonnull) NSString *productId;
@property (nonatomic, copy, readonly, nonnull) NSString *price;
@property (nonatomic, copy, readonly, nonnull) NSString *currency;
@property (nonatomic, copy, readonly, nonnull) NSString *transactionId;
@property (nonatomic, copy, readonly, nonnull) NSDictionary <NSString *, id> *additionalParameters;
@property (nonatomic, copy, readonly, nonnull) NSNumber *priceValue;

@end

NS_ASSUME_NONNULL_END
