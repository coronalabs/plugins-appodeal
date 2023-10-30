#import <Foundation/Foundation.h>
#import <StackMRAIDKit/STKCacheType.h>
#import <StackMRAIDKit/STKMRAIDServiceConfiguration.h>
#import <StackMRAIDKit/STKMRAIDWebConfiguration.h>
#import <StackMRAIDKit/STKMRAIDPresentationConfiguration.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDWrapperConfiguration : NSObject <NSCopying>

@property (nonatomic, assign) STKCacheType cacheType;

@property (nonatomic, copy) STKMRAIDPresentationConfiguration *presentationConfiguration;
@property (nonatomic, copy) STKMRAIDWebConfiguration *webConfiguration;
@property (nonatomic, copy) STKMRAIDServiceConfiguration *serviceConfiguration;

@end

NS_ASSUME_NONNULL_END
