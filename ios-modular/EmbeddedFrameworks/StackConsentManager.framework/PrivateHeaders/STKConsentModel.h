//
//  STKConsentModel.h
//  StackConsentManager
//
//  Created by Stas Kochkin on 10.12.2019.
//  Copyright © 2019 com.stasko. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StackConsentManager/STKVendorModel.h>
#import <StackConsentManager/STKConsentManager.h>
#import <StackConsentManager/STKConsentManagerJSONModelProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKConsentModel : NSObject <NSCopying, NSSecureCoding, STKConsentManagerJSONModel, STKConsent>

@property (nonatomic, readonly, copy) NSArray <STKVendorModel *> *acceptedVendors;
@property (nonatomic, readonly, copy) NSNumber *createdAt;
@property (nonatomic, readonly, copy) NSNumber *updatedAt;
@property (nonatomic, readonly, copy) NSNumber *vendorListVersion;
@property (nonatomic, readonly, copy) NSDictionary <NSString *, id> *iab;
@property (nonatomic, readonly, copy) NSString *payload;

@property (nonatomic, readonly, assign) STKConsentStatus status;
@property (nonatomic, readonly, assign) STKConsentRegulation regulation;

+ (instancetype)userDefinedConsent:(STKConsentStatus)status
                        regulation:(STKConsentRegulation)regulation;

@end

NS_ASSUME_NONNULL_END
