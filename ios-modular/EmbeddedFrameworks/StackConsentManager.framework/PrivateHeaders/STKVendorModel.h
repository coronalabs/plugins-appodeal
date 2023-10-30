//
//  STKVendorModel.h
//  StackConsentManager
//
//  Created by Stas Kochkin on 10.12.2019.
//  Copyright © 2019 com.stasko. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackConsentManager/STKConsentManagerJSONModelProtocol.h>
#import <StackConsentManager/STKVendorBuilder.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKVendorModel : NSObject <NSCopying, NSSecureCoding, STKConsentManagerJSONModel>

@property (nonatomic, copy, readonly) NSNumber *ID;
@property (nonatomic, copy, readonly) NSNumber *iabId;
@property (nonatomic, copy, readonly) NSString *status;
@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, copy, readonly) NSString *policyUrl;

@property (nonatomic, copy, readonly) NSArray <NSNumber *> *featuresIds;
@property (nonatomic, copy, readonly) NSArray <NSNumber *> *purposesIds;
@property (nonatomic, copy, readonly) NSArray <NSNumber *> *legIntPurposeIds;

- (instancetype)initWithBuilder:(STKVendorBuilder *)builder;

@end

NS_ASSUME_NONNULL_END
