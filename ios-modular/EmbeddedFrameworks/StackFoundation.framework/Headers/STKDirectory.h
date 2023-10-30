//
//  STKDirectory.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackFoundation/STKFile.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKDirectory : NSObject

@property (class, nonatomic, readonly) STKDirectory *(^directory)(NSString *name);

@property (nonatomic, readonly) STKFile *_Nullable(^file)(NSString *name);

@property (nonatomic, readonly) void (^save)(STKFile *file, NSString *name, STKSucceededFileBlock _Nullable, STKFailureFileBlock _Nullable);

@end

NS_ASSUME_NONNULL_END
