//
//  APDImage.h
//  Appodeal
//
//  AppodealSDK version 3.9.0
//
//  Copyright © 2025 Appodeal, Inc. All rights reserved.
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
