//
//  AMKWebServiceConfiguration.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *STKMRAIDFeature;

FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsSMS;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsTel;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsCalendar;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsStorePicture;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsInlineVideo;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDSupportsLogging;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDPreloadURL;
FOUNDATION_EXPORT STKMRAIDFeature const kMRAIDMeasure;

@interface STKMRAIDServiceConfiguration : NSObject <NSCopying>

@property (nonatomic, strong, nullable) NSString *partnerName;
@property (nonatomic, strong, nullable) NSString *partnerVersion;
@property (nonatomic, assign) BOOL shouldValidateAd;

- (void)registerServices:(NSArray <STKMRAIDFeature>*)services;

@end

NS_ASSUME_NONNULL_END
