//
//  STKVASTAssetHelper.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/14/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <StackRendering/STKIABAsset.h>
#import <StackRendering/STKVASTAssetTrackProtocol.h>
#import <StackRendering/STKVASTAssetCompanion.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAssetHelper : NSObject

+ (UIInterfaceOrientation)estimatedOrientationBySize:(CGSize)size;

+ (STKIABAssetAspectRatio)aspectRatioBySize:(CGSize)size;

+ (NSUInteger)compareSize:(CGSize)size1
               secondSize:(CGSize)size2
              aspectRatio:(STKIABAssetAspectRatio)currentAspectRatio;

+ (nullable STKVASTAssetCompanion *)companionFromCompanions:(nullable NSArray <STKVASTAssetCompanion *> *)companions
                                                     bySize:(CGSize)size;

+ (NSArray <NSString *> *)tracksFromEvents:(nullable NSArray <id<STKVASTAssetEventTracker>> *)events
                                   byEvent:(STKVASTAssetEvent)event;

+ (nullable NSString *)htmlFromResourceURL:(nullable NSURL *)url
                              clickThrough:(nullable NSURL *)clickThrough
                                      size:(CGSize)size;

+ (nullable NSString *)iFrameHtmlFromResourceURL:(nullable NSURL *)url
                                    clickThrough:(nullable NSURL *)clickThrough
                                            size:(CGSize)size;

+ (nullable NSURL *)cleanURLWithString:(nullable NSString *)string;

+ (NSTimeInterval)timeFromString:(nullable NSString *)stringInterval;

@end


NS_ASSUME_NONNULL_END
