//
//  STKXMLVASTCompanionModel.h
//  StackXML
//
//  Created by Stas Kochkin on 04/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <StackXML/STKXMLModel.h>
#import <AVFoundation/AVFoundation.h>


@interface STKXMLVASTCompanionModel : STKXMLModel

@property (nonatomic, readonly) NSString *width;
@property (nonatomic, readonly) NSString *height;
@property (nonatomic, readonly) NSString *assetWidth;
@property (nonatomic, readonly) NSString *assetHeight;
@property (nonatomic, readonly) NSString *expandedWidth;
@property (nonatomic, readonly) NSString *expandedHeight;
@property (nonatomic, readonly) NSString *apiFramework;
@property (nonatomic, readonly) NSString *creativeType;

@property (nonatomic, readonly) NSString *staticResource;
@property (nonatomic, readonly) NSString *iFrameResource;
@property (nonatomic, readonly) NSString *HTMLResource;
@property (nonatomic, readonly) NSString *adParameters;
@property (nonatomic, readonly) NSString *altText;
@property (nonatomic, readonly) NSArray <NSString *> *clicksThrough;
@property (nonatomic, readonly) NSArray <NSString *> *clicksTracking;
@property (nonatomic, readonly) NSArray <NSDictionary *> *trackingEvents;

- (NSArray *)trackersForName:(NSString *)name;

@end
