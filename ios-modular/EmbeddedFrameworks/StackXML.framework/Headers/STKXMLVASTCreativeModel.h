//
//  STKXMLVASTCreativeModel.h
//  StackXML
//
//  Created by Stas Kochkin on 01/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLModel.h>
#import <StackXML/STKXMLVASTLinearModel.h>
#import <StackXML/STKXMLVASTNonLinearModel.h>
#import <StackXML/STKXMLVASTCompanionModel.h>


@interface STKXMLVASTCreativeModel : STKXMLModel

@property (nonatomic, readonly) NSArray *creativeExtensions;

@property (nonatomic, readonly) STKXMLVASTLinearModel *linear;
@property (nonatomic, readonly) STKXMLVASTNonLinearAdsModel *nonLinear;

@property (nonatomic, readonly) NSArray <STKXMLVASTCompanionModel *> *compainions;

- (void)populateWithCreative:(STKXMLVASTCreativeModel *)creative;

@end
