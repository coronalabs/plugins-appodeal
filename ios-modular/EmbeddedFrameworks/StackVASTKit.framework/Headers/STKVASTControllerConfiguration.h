//
//  STKVASTControllerConfiguration.h
//  StackVASTKit
//
//  Created by Stas Kochkin on 02.10.2020.
//

#import <Foundation/Foundation.h>
#import <StackMRAIDKit/STKCacheType.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKVASTControllerConfigurationBuilder : NSObject

@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendRewarded)(BOOL rewarded);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendAutoclose)(BOOL autoclose);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendMeasuring)(BOOL measuring);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendForceCloseTime)(BOOL forceCloseTime);

@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendCacheType)(STKCacheType cacheType);

@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendPartnerName)(NSString *partnerName);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendPartnerVersion)(NSString *partnerVersion);

@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendCloseTime)(NSTimeInterval closeTime);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendPlaceholderTimeout)(NSTimeInterval placeholderTimeout);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendMaxDuration)(NSTimeInterval maxDuration);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendVideoCloseTime)(NSTimeInterval videoCloseTime);
@property (nonatomic, copy, readonly) STKVASTControllerConfigurationBuilder *(^appendProductParameters)(NSDictionary <NSString *, id> *);

@end


@interface STKVASTControllerConfiguration : NSObject <NSCopying>

@property (nonatomic, assign, readonly, getter=isRewarded) BOOL rewarded;
@property (nonatomic, assign, readonly, getter=isAutoclose) BOOL autoclose;
@property (nonatomic, assign, readonly, getter=isMeasuring) BOOL measuring;
@property (nonatomic, assign, readonly, getter=isForceCloseTime) BOOL forceCloseTime;

@property (nonatomic, assign, readonly) STKCacheType cacheType;

@property (nonatomic, strong, readonly) NSString *partnerName;
@property (nonatomic, strong, readonly) NSString *partnerVersion;

@property (nonatomic, assign, readonly) NSTimeInterval closeTime;
@property (nonatomic, assign, readonly) NSTimeInterval placeholderTimeout;
@property (nonatomic, assign, readonly) NSTimeInterval maxDuration;
@property (nonatomic, assign, readonly) NSTimeInterval videoCloseTime;

@property (nonatomic, copy, readonly) NSDictionary <NSString *, id> *productParameters;

+ (instancetype)configuration:(void(^)(STKVASTControllerConfigurationBuilder *builder))build;

@end

NS_ASSUME_NONNULL_END
