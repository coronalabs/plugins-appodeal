//
//  STKXMLVASTAssetExtensionModel.h
//  StackXML
//
//  Created by Stas Kochkin on 08.10.2020.
//

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLModel.h>


@interface STKXMLVASTAssetExtensionModel : STKXMLModel

@property (nonatomic, readonly) NSString *horizontalPosition;
@property (nonatomic, readonly) NSString *verticalPosition;
@property (nonatomic, readonly) NSString *visible;
@property (nonatomic, readonly) NSString *style;
@property (nonatomic, readonly) NSString *hideafter;
@property (nonatomic, readonly) NSString *shadow;
@property (nonatomic, readonly) NSString *stroke;
@property (nonatomic, readonly) NSString *fill;
@property (nonatomic, readonly) NSString *opacity;
@property (nonatomic, readonly) NSString *outlined;
@property (nonatomic, readonly) NSString *width;
@property (nonatomic, readonly) NSString *height;
@property (nonatomic, readonly) NSString *padding;
@property (nonatomic, readonly) NSString *margin;
@property (nonatomic, readonly) NSString *fontStyle;
@property (nonatomic, readonly) NSString *strokeWidth;

@property (nonatomic, readonly) NSString *content;

@end
