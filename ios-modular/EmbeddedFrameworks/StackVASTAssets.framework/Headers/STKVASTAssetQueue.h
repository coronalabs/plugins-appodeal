//
//  STKVASTAssetQueue.h
//  StackVASTKit
//
//  Created by Stanislau Rubasheuski on 13.05.22.
//

#import <StackVASTAssets/STKVASTAssetProvider.h>

@class STKVASTAssetQueue;

NS_ASSUME_NONNULL_BEGIN

@protocol STKVASTAssetQueueDelegate <NSObject>
/**
 Called after successful parsing document by STKVASTAssetProvider

 @param queue Current queue
 @param document VAST XML Document
 */
- (void)queue:(STKVASTAssetQueue *)queue didLoadDocument:(NSString *)document;
/**
 Called if document parsing did fail by STKVASTAssetProvider

 @param queue Current queue
 @param error Document parsing error with parsing error code
 */
- (void)queue:(STKVASTAssetQueue *)queue failToLoadWithError:(NSError *)error;

@end


@interface STKVASTAssetQueue : NSObject
/**
 Designated initializer

 @param url VAST XML Document url
 @param delegate Delegate
 @return Return nonnull class instance
 */
+ (instancetype)queueWithURL:(nullable NSURL *)url
                    delegate:(nullable id<STKVASTAssetQueueDelegate>)delegate;
/**
 Designated initializer

 @param data VAST XML Document data
 @param delegate Delegate
 @return Return nonnull class instance
 */
+ (instancetype)queueWithData:(nullable NSData *)data
                     delegate:(nullable id<STKVASTAssetQueueDelegate>)delegate;
/**
 Return actual asset
 */
- (STKVASTAsset *)asset;
/**
 Return true if queue has next available asset for playing
 */
- (BOOL)isQueueHasNextAsset;
/**
 Return product link for concrete asset companion.
 */
- (nullable NSString *)productLinkForAssetCompanion:(nullable STKVASTAssetCompanion *)companion;
/**
 Remove first asset in queue
 */
- (void)changeCurrentAsset;
/**
 Return true if assets > 1
 */
- (BOOL)multipleAssets;
/**
 Return actual AD count asset
 */
- (STKIABAsset *)adCountAsset;

@end

NS_ASSUME_NONNULL_END
