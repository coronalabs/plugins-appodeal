//
//  STKXMLVASTIconModel.h
//  StackXML
//
//  Created by Stas Kochkin on 03/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <StackRendering/STKXMLModel.h>

@interface STKXMLVASTIconModel : STKXMLModel

@property (nonatomic, readonly) NSString *width;
@property (nonatomic, readonly) NSString *height;
@property (nonatomic, readonly) NSString *xPosition;
@property (nonatomic, readonly) NSString *yPosition;
@property (nonatomic, readonly) NSString *duration;
@property (nonatomic, readonly) NSString *apiFramework;
@property (nonatomic, readonly) NSString *staticResource;
@property (nonatomic, readonly) NSString *iFrameResource;
@property (nonatomic, readonly) NSString *HTMLResource;
@property (nonatomic, readonly) NSString *clickThrough;
@property (nonatomic, readonly) NSString *clickTracking;
@property (nonatomic, readonly) NSString *viewTracking;

@end
