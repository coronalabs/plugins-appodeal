//
//  AMKWebAdConfiguration.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <StackRendering/STKScriptMessageHandlerProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDWebConfiguration : NSObject<NSCopying>

@property (nonatomic, readonly) NSString *baseUrl;

@property (nonatomic, readonly) double timeout;

@property (nonatomic, readonly) WKUserContentController *contentController;

@property (nonatomic, readonly) void(^appendScript)(WKUserScript *);

@property (nonatomic, readonly) void(^appendMessageHandler)(id<STKScriptMessageHandler>);

@property (nonatomic, readonly) void(^appendBaseUrl)(NSString *);

@property (nonatomic, readonly) void(^appendTimeout)(double);

@end

NS_ASSUME_NONNULL_END
