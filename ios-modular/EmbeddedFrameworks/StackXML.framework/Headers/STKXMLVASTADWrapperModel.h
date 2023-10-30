//
//  STKXMLVASTADWrapperModel.h
//  StackVASTKit
//
//  Created by Stanislau Rubasheuski on 6.05.22.
//

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLModel.h>
#import <StackXML/STKXMLVASTWrapperModel.h>


@interface STKXMLVASTADWrapperModel: STKXMLModel

@property (nonatomic, readonly) NSString *ID;
@property (nonatomic, readonly) NSNumber *sequence;
@property (nonatomic, readonly) STKXMLVASTWrapperModel *wrapper;

- (void)populateWithADWrapper:(STKXMLVASTADWrapperModel *)adWrapper;

@end
