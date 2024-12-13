#import <Foundation/Foundation.h>
#import <StackRendering/STKCacheType.h>
#import <StackRendering/STKMRAIDServiceConfiguration.h>
#import <StackRendering/STKMRAIDWebConfiguration.h>
#import <StackRendering/STKMRAIDPresentationConfiguration.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDWrapperConfiguration : NSObject <NSCopying>

@property (nonatomic, assign) STKCacheType cacheType;

@property (nonatomic, copy) STKMRAIDPresentationConfiguration *presentationConfiguration;
@property (nonatomic, copy) STKMRAIDWebConfiguration *webConfiguration;
@property (nonatomic, copy) STKMRAIDServiceConfiguration *serviceConfiguration;

@end

NS_ASSUME_NONNULL_END
