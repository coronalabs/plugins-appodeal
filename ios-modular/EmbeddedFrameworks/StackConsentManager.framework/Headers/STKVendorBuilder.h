//
//  STKVendorBuilder.h
//  StackConsentManager
//
//  Created by Stas Kochkin on 13.12.2019.
//  Copyright © 2019 com.stasko. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Builder for custom vendors
@interface STKVendorBuilder : NSObject
/// Append displayed name in consent dialog
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendName)(NSString *);
/// Append status to check consent result by manager
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendBundle)(NSString *);
/// Append privacy policy URL
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendPolicyURL)(NSURL *);
/// Append iAB features identifiers
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendFeaturesIds)(NSArray<NSNumber *> *);
/// Append iAB purposes identifiers
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendPurposesIds)(NSArray<NSNumber *> *);
/// Append iAB legint purposes identifiers
@property (nonatomic, copy, readonly) STKVendorBuilder *(^appendLegIntPurposeIds)(NSArray<NSNumber *> *);
@end

NS_ASSUME_NONNULL_END
