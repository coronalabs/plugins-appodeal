//
//  STKNativeLogRecorder.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackModules/STKLoggerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKNativeLogRecorder : NSObject <STKLogRecorder>

@property (nonatomic, strong, nullable) STKLogCategory category;

@end

NS_ASSUME_NONNULL_END
