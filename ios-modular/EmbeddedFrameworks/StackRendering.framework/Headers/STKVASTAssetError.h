//
//  STKVASTAssetError.h
//  StackVASTAssets
//
//  Created by Ilia Lozhkin on 12/27/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>

// Mirror STKXMLVASTErrorCode
typedef NS_ENUM(NSInteger, STKVASTAssetErrorCode) {
    STKVASTAssetNoError = 0,
    STKVASTAssetParsingError = 100,                  // VAST Parsing error (document == nil || xmlDocument == nil)
    STKVASTAssetValidationError = 101,               // VAST Validation error (xmlDocument.tag != vast)
    STKVASTAssetExpectedDurationError = 202,         // VAST Video duration not compatible
    STKVASTAssetGeneralWrapperError = 300,           // VAST Wrapper error (wrapper.attribute)
    STKVASTAssetURIConnectionError = 301,            // VAST Network error (wrapper.URI == nil, wrapper.response.error)
    STKVASTAssetWrapperDeepError = 302,              // VAST Wrapper capacity (wrapper <= maxWrapperCount)
    STKVASTAssetWrapperNoAdsResponseError = 303,     // VAST No Ad (wrapper.response.code == 204, wrapper.ad.count == 0)
    STKVASTAssetNoFileError = 401,                   // VAST No file (inLine == nil)
    STKVASTAssetNoValidFileAttributeError = 403,     // VAST No Required attribute (media.requiredFields is empty)
    STKVASTAssetProblemFileError = 405,              // VAST Problec file (MIME_TYPE not supported)
    STKVASTAssetCompanionError = 600,                // VAST Postbanner companion error (companion.postbanner.count == nil)
    STKVASTAssetUndefinedError = 900                 // VAST Undefined error
};


NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAssetError : NSError

+ (STKVASTAssetError *(^)(STKVASTAssetErrorCode, NSString *_Nullable))error;

+ (STKVASTAssetError *(^)(STKVASTAssetErrorCode))errorWithCode;

+ (STKVASTAssetError *(^)(STKVASTAssetErrorCode, NSError *_Nullable))errorWithError;

@end

NS_ASSUME_NONNULL_END
