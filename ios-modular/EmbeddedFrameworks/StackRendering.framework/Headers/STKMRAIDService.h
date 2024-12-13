//
//  AMKWebServiceManager.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackRendering/STKMRAIDServiceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKMRAIDServiceDelegate <NSObject>

@optional

- (void)mraidServiceCreateCalendarEventWithEventJSON:(NSString *)eventJSON;

- (void)mraidServicePlayVideoWithUrlString:(NSString *)urlString;

- (void)mraidServiceStorePictureWithUrlString:(NSString *)urlString;

- (void)mraidServiceDidReceiveLogMessage:(NSString *)message;

@end

@interface STKMRAIDService : NSObject

@property (nonatomic, copy, readonly) STKMRAIDServiceConfiguration *configuration;

@property (nonatomic, weak) id<STKMRAIDServiceDelegate> delegate;

@property (nonatomic, readonly) void(^appendConfiguration)(STKMRAIDServiceConfiguration *);

@end

NS_ASSUME_NONNULL_END
