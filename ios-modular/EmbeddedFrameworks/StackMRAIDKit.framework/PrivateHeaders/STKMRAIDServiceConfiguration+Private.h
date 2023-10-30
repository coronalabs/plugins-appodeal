//
//  AMKWebServiceConfiguration+Private.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackMRAIDKit/STKMRAIDServiceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDServiceConfiguration (Private)

@property (nonatomic, strong, readonly) NSArray <STKMRAIDFeature> *serviceFeatures;
@property (nonatomic, strong, readonly) NSArray <STKMRAIDFeature> *internalServiceFeatures;

@end

NS_ASSUME_NONNULL_END
