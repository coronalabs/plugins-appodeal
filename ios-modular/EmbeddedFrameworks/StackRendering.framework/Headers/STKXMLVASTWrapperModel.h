//
//  STKXMLVASTWrapperModel.h
//  StackXML
//
//  Created by Stas Kochkin on 01/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKXMLModel.h>
#import <StackRendering/STKXMLVASTCreativeModel.h>
#import <StackRendering/STKXMLVASTExtensionModel.h>

typedef struct STKXMLVASTWrapperOptions {
    BOOL STKXMLVASTFallbackAd; //      YES - разрешен опрос следущего объекта если враппер зафейлился
    BOOL STKXMLVASTMultipleAds; //     YES - разрешена поддержка нескольких объекктов в ответе с враппера
    BOOL STKXMLVASTFollowWrapper; //   YES - разрешена загрузка врапперов
} STKXMLVASTWrapperOptions;

extern const STKXMLVASTWrapperOptions STKXMLVASTWrapperOptionsZero;

@interface STKXMLVASTWrapperModel : STKXMLModel

@property (nonatomic, readonly) STKXMLVASTWrapperOptions options;

@property (nonatomic, readonly) NSString *vastTagURI;
@property (nonatomic, readonly) NSString *adSystem;

@property (nonatomic, readonly) NSArray <NSString *> *errors;
@property (nonatomic, readonly) NSArray <NSString *> *impressions;

@property (nonatomic, readonly) NSArray <STKXMLVASTCreativeModel *> *creatives;
@property (nonatomic, readonly) NSArray <STKXMLVASTExtensionModel *> *extensions;

- (void)populateWithWrapper:(STKXMLVASTWrapperModel *)wrapper;

@end
