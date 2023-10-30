//
//  STKStreamingLogRecorder.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackFoundation/STKLoggerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKStreamingLogRecorder :  NSObject <STKLogRecorder>

@property (nonatomic, strong, nullable) STKLogCategory category;

- (instancetype)initWithStorageName:(NSString *)name;

- (void)clearStorage;

- (NSString *_Nullable)storageLog;

@end

NS_ASSUME_NONNULL_END
