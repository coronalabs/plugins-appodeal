//
//  STKVASTAssetAsset+Private.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/14/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <StackVASTAssets/STKVASTAsset.h>
#import <StackXML/StackXML.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAsset (Private)

+ (nullable instancetype)assetWithInLine:(nullable STKXMLVASTInLineModel *)inLine __deprecated_msg("use: assetWithInLine:error:");

/**
 Designated initializer

 @param inLine VAST IAB model
 @param error Autoreleasing error. Return 401 code if File not found
 @return Return nonnull class instance
 */
+ (instancetype)assetWithInLine:(nullable STKXMLVASTInLineModel *)inLine error:(NSError *_Nullable __autoreleasing *)error;

/**
 New initializer

 @param adInLine VAST IAB model
 @param error Autoreleasing error. Return 401 code if File not found
 @return Return nonnull class instance
 */
+ (instancetype)assetWithADInLine:(nullable STKXMLVASTADInLineModel *)adInLine error:(NSError *_Nullable __autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
