//
//  STKNASTManager.h
//  StackNASTKit
//
//  Created by Lozhkin Ilya on 5/31/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKNASTAd.h>
#import <StackRendering/STKNASTDefines.h>


/**
 Manager completion error

 @param ad Parsed native ad model
 @param error Error occures while parsing/loading
 */
typedef void(^STKNASTCompletionBlock)(STKNASTAd * _Nullable ad, NSError * _Nullable error);

/**
 Manager for loading and parsing NAST model
 */
@interface STKNASTManager : NSObject
/**
 Comparator that provides association between model ids and server
 response id. Keys should be @(STKNASTAssetID) and values should
 be relative id's from response
 */
@property (nonatomic, strong, nonnull) NSDictionary <NSNumber *, NSNumber *> * assetComparator;
/**
 Download and parse NAST model from remote URL

 @param url Remote URL to model
 @param completion Completion  block
 */
- (void)loadAdFromURL:(nonnull NSURL *)url
           completion:(nonnull STKNASTCompletionBlock)completion;
/**
 Parse NAST model from given JSON

 @param JSON NAST JSON
 @param completion Completion block
 */
- (void)parseAdFromJSON:(nonnull NSDictionary <NSString *, id>*)JSON
             completion:(nonnull STKNASTCompletionBlock)completion;

@end
