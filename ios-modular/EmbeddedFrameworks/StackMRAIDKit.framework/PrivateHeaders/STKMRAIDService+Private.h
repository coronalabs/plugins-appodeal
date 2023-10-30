//
//  AMKWebServiceManager+Private.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackMRAIDKit/STKMRAIDService.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDService (Actions)

- (void)createCalendarEvent:(NSString *)event;

- (void)storePicture:(NSURL *)url;

- (void)playVideo:(NSURL *)url;

- (void)open:(NSURL *)url;

- (void)receiveMessage:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
