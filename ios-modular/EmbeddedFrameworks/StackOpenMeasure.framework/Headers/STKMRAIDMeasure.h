//
//  STKMRAIDMeasure.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 1/30/20.
//  Copyright © 2020 Appodeal. All rights reserved.
//

#import <StackOpenMeasure/STKMeasureEventProtocol.h>
#import <StackOpenMeasure/STKMeasureBuilderProtocol.h>
#import <StackOpenMeasure/STKMeasureViewContextProtocol.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDMeasure : NSObject <STKMeasureEventProtocol>

@property (nonatomic, strong, readonly) id<STKMeasureViewContextProtocol> context;

+ (instancetype)measureWithBuilder:(void(^)(id<STKMRAIDMeasureBuilderProtocol>))builder;

- (void)startSession:(NSError * _Nullable __autoreleasing *)error;

- (void)finishSession;

+ (instancetype)new __unavailable;

- (instancetype)init __unavailable;

@end

NS_ASSUME_NONNULL_END
