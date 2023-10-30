//
//  STKNetworkSession.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackFoundation/STKFile.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^STKSessionJSONCallback)(NSDictionary *_Nullable, NSError *_Nullable);
typedef void(^STKSessionDataCallback)(NSData *_Nullable, NSError *_Nullable);
typedef void(^STKSessionLocationCallback)(STKFile *_Nullable, NSError *_Nullable);


@interface STKNetworkSession : NSObject

@property (class, nonatomic, readonly) STKNetworkSession *session;

@property (nonatomic, readonly) void(^loadJSON)(NSURLRequest *_Nullable, _Nullable STKSessionJSONCallback);
@property (nonatomic, readonly) void(^loadData)(NSURLRequest *_Nullable, _Nullable STKSessionDataCallback);
@property (nonatomic, readonly) void(^downloadData)(NSURLRequest *_Nullable, _Nullable STKSessionLocationCallback);

- (NSData *_Nullable)performSynchronousRequestWithUrlString:(NSString *_Nullable)url
                                                      error:(NSError **_Nullable)error;

- (NSData *_Nullable)performSynchronousRequest:(NSURLRequest *_Nullable)request
                                         error:(NSError **_Nullable)error;

- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
