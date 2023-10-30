//
//  STKMeasureBuilderProtocol.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 22.02.2021.
//  Copyright © 2021 Appodeal. All rights reserved.
//

#import <WebKit/WebKit.h>
#import <StackOpenMeasure/STKVASTMeasureResources.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKMeasureBuilderProtocol <NSObject>

@property (nonatomic, readonly) id<STKMeasureBuilderProtocol> (^appendPartnerVersion)(NSString *);

@property (nonatomic, readonly) id<STKMeasureBuilderProtocol> (^appendPartnerName)(NSString *);

@end

@protocol STKMRAIDMeasureBuilderProtocol <STKMeasureBuilderProtocol>

@property (nonatomic, readonly) id<STKMRAIDMeasureBuilderProtocol> (^appendWebView)(WKWebView *);

@end

@protocol STKVASTMeasureBuilderProtocol <STKMeasureBuilderProtocol>

@property (nonatomic, readonly) id<STKVASTMeasureBuilderProtocol> (^appendResources)(NSArray<STKVASTMeasureResources *> *);

@property (nonatomic, readonly) id<STKVASTMeasureBuilderProtocol> (^appendSkippable)(BOOL);

@property (nonatomic, readonly) id<STKVASTMeasureBuilderProtocol> (^appendAutoplay)(BOOL);

@property (nonatomic, readonly) id<STKVASTMeasureBuilderProtocol> (^appendSkipOffset)(CGFloat);

@property (nonatomic, readonly) id<STKVASTMeasureBuilderProtocol> (^appendDuration)(CGFloat);

@end

NS_ASSUME_NONNULL_END
