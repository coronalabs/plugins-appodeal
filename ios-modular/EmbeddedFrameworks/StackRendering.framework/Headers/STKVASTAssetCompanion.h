//
//  STKVASTAssetAssetCompanion.h
//  Appodeal
//
//  Created by Ilia Lozhkin on 12/14/18.
//  Copyright © 2018 Appodeal, Inc. All rights reserved.
//

#import <StackRendering/STKVASTAssetTrackProtocol.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger,  STKVASTContentType) {
    STKVASTContentTypeStaticImage = 0,
    STKVASTContentTypeIframe,
    STKVASTContentTypeHTML
};

NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAssetCompanion : NSObject
/**
 Companion creative size. Default CGSizeZero
 */
@property (nonatomic, assign, readonly) CGSize size;
/**
 Type of companion creative content
 */
@property (nonatomic, assign, readonly) STKVASTContentType contentType;
/**
 Content
    - StaticImage from URL (Local HTML)
    - Iframe (Local HTML)
    - Local HTML
 */
@property (nonatomic, copy, readonly, nullable) NSString *content;
/**
 URL of HTML document
 */
@property (nonatomic, copy, readonly, nullable) NSURL *contentURL;

@end

@interface STKVASTAssetCompanion (STKVASTAssetTrack)
/**
 Companion track model
 */
@property (nonatomic, copy, readonly) id <STKVASTAssetTrack> track;

@end

@interface STKVASTAssetCompanion (STKVASTAssetExtension)
/**
 Companion close time from extensions. Default - 0
 */
@property (nonatomic, assign, readonly) NSTimeInterval closeTime;

@end

NS_ASSUME_NONNULL_END
