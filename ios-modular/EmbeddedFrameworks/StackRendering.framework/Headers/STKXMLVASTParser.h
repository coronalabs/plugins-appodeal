//
//  STKXMLVASTParser.h
//  StackXML
//
//  Created by Stas Kochkin on 01/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>

@class STKXMLVASTADInLineModel;


@interface STKXMLVASTParser : NSObject

- (void)parseContentsOfURL:(NSURL *)URL
                   success:(void(^)(NSArray <STKXMLVASTADInLineModel *>*, NSString *))success
                   failure:(void(^)(NSError *))failure;

- (void)parseContentsOfDocument:(NSData *)document
                        success:(void(^)(NSArray <STKXMLVASTADInLineModel *>*, NSString *))success
                        failure:(void(^)(NSError *))failure;

@end
