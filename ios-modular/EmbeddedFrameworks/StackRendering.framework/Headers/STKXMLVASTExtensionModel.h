//
//  STKXMLVASTExtensionModel.h
//  StackXML
//
//  Created by Stas Kochkin on 07/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <StackRendering/STKXMLModel.h>
#import <StackRendering/STKXMLVASTCompanionModel.h>
#import <StackRendering/STKXMLVASTVerificationModel.h>
#import <StackRendering/STKXMLVASTAssetExtensionModel.h>
#import <StackRendering/STKXMLVASTPostbannerExtensionModel.h>


@interface STKXMLVASTExtensionModel : STKXMLModel

@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *content;

@property (nonatomic, readonly) NSString *videoClickable;
@property (nonatomic, readonly) NSString *videoMuted;
@property (nonatomic, readonly) NSString *closeTime;
@property (nonatomic, readonly) NSString *companionShow;
@property (nonatomic, readonly) NSString *bmSKOverlayShow;
@property (nonatomic, readonly) NSString *skOverlayShow;
@property (nonatomic, readonly) NSString *productLink;
@property (nonatomic, readonly) NSString *r1;
@property (nonatomic, readonly) NSString *r2;
@property (nonatomic, readonly) NSString *r3;
@property (nonatomic, readonly) NSString *autorotate;
@property (nonatomic, readonly) NSString *companionCloseTime;
@property (nonatomic, readonly) NSString *ignoresSafeAreaLayoutGuide;
@property (nonatomic, readonly) NSString *forceOrientation;

@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *CTAAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *muteAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *progressAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *countdownAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *closeAsset;
@property (nonatomic, readonly) STKXMLVASTAssetExtensionModel *videoAsset;

@property (nonatomic, readonly) STKXMLVASTCompanionModel *companion;
@property (nonatomic, readonly) STKXMLVASTPostbannerExtensionModel *postbanner;
@property (nonatomic, readonly) NSArray <STKXMLVASTVerificationModel*> *verifications;

// Legacy
@property (nonatomic, readonly) NSString *CTAText;
@property (nonatomic, readonly) NSString *CTAShow;
@property (nonatomic, readonly) NSString *muteShow;
@property (nonatomic, readonly) NSString *progressShow;
@property (nonatomic, readonly) NSString *assetStrokeColor;
@property (nonatomic, readonly) NSString *assetFillColor;
@property (nonatomic, readonly) NSString *CTAXPosition;
@property (nonatomic, readonly) NSString *CTAYPosition;
@property (nonatomic, readonly) NSString *muteXPosition;
@property (nonatomic, readonly) NSString *muteYPosition;
@property (nonatomic, readonly) NSString *closeXPosition;
@property (nonatomic, readonly) NSString *closeYPosition;

@end
