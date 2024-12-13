//
//  STKXMLVASTNonLinearModel.h
//  StackXML
//
//  Created by Stas Kochkin on 04/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <StackRendering/STKXMLModel.h>

@class STKXMLVASTNonLinearModel;

@interface STKXMLVASTNonLinearAdsModel : STKXMLModel

@property (nonatomic, readonly) NSArray <STKXMLVASTNonLinearModel *> *nonLinearAds;
@property (nonatomic, readonly) NSArray <NSDictionary *> *trackingEvents;

- (void)populateWithNonLinear:(STKXMLVASTNonLinearAdsModel *)nonLinear;

@end

@interface STKXMLVASTNonLinearModel : STKXMLModel

@property (nonatomic, readonly) NSString *width;
@property (nonatomic, readonly) NSString *height;
@property (nonatomic, readonly) NSString *expandedWidth;
@property (nonatomic, readonly) NSString *expandedHeight;
@property (nonatomic, readonly) NSString *scalable;
@property (nonatomic, readonly) NSString *maintainAspectRatio;
@property (nonatomic, readonly) NSString *minSuggestedDuration;
@property (nonatomic, readonly) NSString *apiFramework;

@property (nonatomic, readonly) NSString *staticResource;
@property (nonatomic, readonly) NSString *iFrameResource;
@property (nonatomic, readonly) NSString *HTMLResource;
@property (nonatomic, readonly) NSString *adParameters;
@property (nonatomic, readonly) NSString *clickThrough;
@property (nonatomic, readonly) NSString *clickTracking;

@end
