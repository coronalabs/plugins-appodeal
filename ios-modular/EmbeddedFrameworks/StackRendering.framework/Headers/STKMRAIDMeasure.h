//
//  STKMRAIDMeasure.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 1/30/20.
//  Copyright © 2020 Appodeal. All rights reserved.
//

#import <StackRendering/STKMeasureError.h>
#import <StackRendering/STKMeasureEventProtocol.h>
#import <StackRendering/STKMeasureBuilderProtocol.h>
#import <StackRendering/STKMeasureViewContextProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDMeasure : NSObject <STKMeasureEventProtocol>

@property (nonatomic, strong, readonly) id<STKMeasureViewContextProtocol> context;

+ (instancetype)measureWithBuilder:(void(^)(id<STKMRAIDMeasureBuilderProtocol>))builder;

- (void)startSession:(NSError * _Nullable __autoreleasing *)error;
- (void)logErrorWithType:(STKMeasureErrorType)type message:(NSString *)message;
- (void)finishSession;

- (void)adUserInteraction;

+ (instancetype)new __unavailable;

- (instancetype)init __unavailable;

@end

NS_ASSUME_NONNULL_END
