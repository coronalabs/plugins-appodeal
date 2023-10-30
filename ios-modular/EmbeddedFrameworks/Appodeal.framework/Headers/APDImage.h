//
//  APDImage.h
//  Appodeal
//
//  AppodealSDK version 3.2.0-beta.1
//
//  Copyright © 2023 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 Instance of this class contains URL to image source and size of image
 */
@interface APDImage : NSObject
/**
 Url to image source. Can be local
 */
@property (nonatomic, strong, readonly, nullable) NSURL *url;
@property (nonatomic, strong, readonly, nullable) UIImage *image;

@end
