//
//  STKSystemLogRecorder.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackFoundation/STKLoggerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKSystemLogRecorder : NSObject <STKLogRecorder>

@property (nonatomic, strong, nullable) STKLogCategory category;

@end

NS_ASSUME_NONNULL_END
