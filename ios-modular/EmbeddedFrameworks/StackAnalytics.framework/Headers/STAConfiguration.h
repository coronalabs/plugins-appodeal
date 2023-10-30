//
//  STKAnalyticsConfiguration.h
//  StackAnalytics
//
//  Created by Stas Kochkin on 13.07.2021.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(AnalyticsConfiguration)
@interface STAConfiguration : NSObject <NSCopying>

@property (nonatomic, copy, readwrite) NSURL *baseURL;
@property (nonatomic, copy, readwrite) NSDictionary <NSString *, id> *extras;
@property (nonatomic, assign, readwrite) NSTimeInterval reportInterval;
@property (nonatomic, assign, readwrite) NSUInteger size;
@property (nonatomic, assign, readwrite) BOOL debug;

- (instancetype)initWithURL:(NSURL *)url
                   interval:(NSTimeInterval)interval
                       size:(NSUInteger)size
                      debug:(BOOL)debug
                     extras:(NSDictionary <NSString *, id> *)extras;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
