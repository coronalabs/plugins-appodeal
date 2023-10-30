//
//  STKVASTAssetCache.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/14/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <StackVASTAssets/STKVASTAsset.h>

@class STKVASTAssetProvider;


NS_ASSUME_NONNULL_BEGIN

@protocol STKVASTAssetCacheDelegate <NSObject>
/**
 Called after successful parsing document

 @param asset Current Asset
 @param document VAST XML Document
 */
- (void)asset:(STKVASTAssetProvider *)asset didLoadDocument:(NSString *)document;
/**
 Called if document parsing did fail

 @param asset Current Asset
 @param error Document parsing error with parsing error code
 */
- (void)asset:(STKVASTAssetProvider *)asset failToLoadWithError:(NSError *)error;

@end

@interface STKVASTAssetProvider : NSObject
/**
 Vast assets model
 */
@property (nonatomic, readonly, nullable) NSArray <STKVASTAsset *> *assets;
/**
 Designated initializer

 @param url VAST XML Document url
 @param delegate Delegate
 @return Return nonnull class instance
 */
+ (instancetype)assetWithURL:(nullable NSURL *)url
                    delegate:(nullable id<STKVASTAssetCacheDelegate>)delegate;
/**
 Designated initializer

 @param data VAST XML Document data
 @param delegate Delegate
 @return Return nonnull class instance
 */
+ (instancetype)assetWithData:(nullable NSData *)data
                     delegate:(nullable id<STKVASTAssetCacheDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
