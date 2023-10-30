//
//  STKXMLVASTPostbannerExtensionModel.h
//  StackXML
//
//  Created by Stas Kochkin on 15.12.2020.
//

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLVASTAssetExtensionModel.h>


@interface STKXMLVASTPostbannerExtensionModel : STKXMLModel

@property (nonatomic, readonly) NSString *useNativeClose;
@property (nonatomic, readonly) NSString *closeTime;
@property (nonatomic, readonly) NSString *r1;
@property (nonatomic, readonly) NSString *r2;
@property (nonatomic, readonly) NSString *ignoresSafeAreaLayoutGuide;
@property (nonatomic, readonly) NSString *productLink;
@property (nonatomic, readonly) NSString *duration;

@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *countdownAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *closeAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *progressAsset;

@end

