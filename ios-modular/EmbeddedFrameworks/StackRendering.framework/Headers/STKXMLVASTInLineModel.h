//
//  STKXMLVASTDocumentModel.h
//  StackXML
//
//  Created by Stas Kochkin on 01/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKXMLModel.h>
#import <StackRendering/STKXMLVASTCreativeModel.h>
#import <StackRendering/STKXMLVASTWrapperModel.h>
#import <StackRendering/STKXMLVASTExtensionModel.h>


@interface STKXMLVASTInLineModel : STKXMLModel

@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) NSString *advertiser;
@property (nonatomic, readonly) NSString *adSystem;
@property (nonatomic, readonly) NSString *adDescription;

@property (nonatomic, readonly) NSArray <NSString *> *errors;
@property (nonatomic, readonly) NSArray <NSString *> *impressions;

@property (nonatomic, readonly) NSArray <STKXMLVASTExtensionModel *> *extensions;
@property (nonatomic, readonly) NSArray <STKXMLVASTCreativeModel *> *creatives;

- (void)populateWithWrapper:(STKXMLVASTWrapperModel *)wrapper;

@end
