//
//  STKNASTAd.h
//  StackNASTKit
//
//  Created by Lozhkin Ilya on 5/31/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackXML/StackXML.h>

/**
 NAST Model
 */
@interface STKNASTAd : NSObject
/**
 Impression trackers
 */
@property (strong, nonatomic, readonly, nullable) NSArray <NSURL *> * impressionTrackers;
/**
 Finish trackers
 */
@property (strong, nonatomic, readonly, nullable) NSArray <NSURL *> * finishTrackers;
/**
 Click through urls
 */
@property (strong, nonatomic, readonly, nonnull) NSArray <NSURL *> * clickThrough;
/**
 Click trackers urls
 */
@property (strong, nonatomic, readonly, nullable) NSArray <NSURL *> * clickTrackers;
/**
 Title of ad
 */
@property (copy, nonatomic, readonly, nonnull) NSString * title;
/**
 Description text of ad
 */
@property (copy, nonatomic, readonly, nullable) NSString * descriptionText;
/**
 CTA text
 */
@property (copy, nonatomic, readonly, nullable) NSString * callToAction;
/**
 Star rating
 */
@property (copy, nonatomic, readonly, nullable) NSNumber * starRating;
/**
 Remote url to icon
 */
@property (strong, nonatomic, readonly, nonnull) NSString * iconURLString;
/**
 Remote url to main image
 */
@property (strong, nonatomic, readonly, nullable) NSString * mainURLString;
/**
 VAST string
 */
@property (strong, nonatomic, readonly, nullable) NSString * rawVAST;

/**
 VAST InLine model
 */
@property (strong, nonatomic, readonly, nullable) STKXMLVASTInLineModel *VASTInLineModel;

/**
 Custom NAST params
 */
@property (strong, nonatomic, readonly, nonnull) NSDictionary *customParams;

@end
