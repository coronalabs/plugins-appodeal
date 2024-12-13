//
//  STKXMLVASTVerificationModel.h
//  StackXML
//
//  Created by Ilia Lozhkin on 1/31/20.
//

#import <StackRendering/STKXMLModel.h>

@interface STKXMLVASTVerificationModel : STKXMLModel

@property (nonatomic, readonly) NSString * vendor;
@property (nonatomic, readonly) NSString * javaScriptResource;
@property (nonatomic, readonly) NSString * verificationParameters;

@end
