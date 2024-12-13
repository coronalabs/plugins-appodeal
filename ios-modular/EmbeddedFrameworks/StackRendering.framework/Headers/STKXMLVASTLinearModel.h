//
//  STKXMLVASTLinearModel.h
//  StackXML
//
//  Created by Stas Kochkin on 03/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKXMLModel.h>
#import <StackRendering/STKXMLVASTIconModel.h>
#import <StackRendering/STKXMLVASTCompanionModel.h>

@class STKXMLVASTLinearModel;

static NSString *const kSTKXMLVASTTrackingFirstQuartile   = @"firstQuartile";
static NSString *const kSTKXMLVASTTrackingMidpoint        = @"midpoint";
static NSString *const kSTKXMLVASTTrackingThirdQuartile   = @"thirdQuartile";
static NSString *const kSTKXMLVASTTrackingComplete        = @"complete";
static NSString *const kSTKXMLVASTTrackingMute            = @"mute";
static NSString *const kSTKXMLVASTTrackingUnmute          = @"unmute";
static NSString *const kSTKXMLVASTTrackingPause           = @"pause";
static NSString *const kSTKXMLVASTTrackingResume          = @"resume";
static NSString *const kSTKXMLVASTTrackingFullscreen      = @"fullscreen";
static NSString *const kSTKXMLVASTTrackingClose           = @"close";
static NSString *const kSTKXMLVASTTrackingStart           = @"start";
static NSString *const kSTKXMLVASTTrackingCreativeView    = @"creativeView";
static NSString *const kSTKXMLVASTTrackingSkipp           = @"skip";
static NSString *const kSTKXMLVASTTrackingExpand          = @"expand";
static NSString *const kSTKXMLVASTTrackingCollapse        = @"collapse";
static NSString *const kSTKXMLVASTTrackingRewind          = @"rewind";
static NSString *const kSTKXMLVASTTrackingInvitaion       = @"acceptInvitation";

@interface STKXMLVASTMediaFileModel: STKXMLModel

@property (nonatomic, readonly) NSString *delivery;
@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *bitrate;
@property (nonatomic, readonly) NSString *maxBitrate;
@property (nonatomic, readonly) NSString *minBitrate;
@property (nonatomic, readonly) NSString *width;
@property (nonatomic, readonly) NSString *height;
@property (nonatomic, readonly) NSString *scalable;
@property (nonatomic, readonly) NSString *maintainAspectRatio;
@property (nonatomic, readonly) NSString *apiFramework;
@property (nonatomic, readonly) NSString *content;
@property (nonatomic, readonly) NSString *skipoffset;
@property (nonatomic, readonly) NSString *duration;

-(void)populateWithLinear:(STKXMLVASTLinearModel *)model;

@end


@interface STKXMLVASTLinearModel : STKXMLModel

@property (nonatomic, readonly) NSString *skipoffset;
@property (nonatomic, readonly) NSString *adParameters;
@property (nonatomic, readonly) NSString *duration;

@property (nonatomic, readonly) NSArray <STKXMLVASTMediaFileModel *> *mediafiles;
@property (nonatomic, readonly) NSArray <STKXMLVASTIconModel *> *icons;

@property (nonatomic, readonly) NSArray <NSDictionary *> *trackingEvents;
@property (nonatomic, readonly) NSArray <NSString *> *clicksThrough;
@property (nonatomic, readonly) NSArray <NSString *> *clicksTracking;
@property (nonatomic, readonly) NSArray <NSString *> *customClicks;

- (void)populateWithLinear:(STKXMLVASTLinearModel *)linear;

@end
