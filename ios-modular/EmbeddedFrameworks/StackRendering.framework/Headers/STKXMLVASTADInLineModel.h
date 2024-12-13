//
//  STKXMLVASTADInLineModel.h
//  StackVASTKit
//
//  Created by Stanislau Rubasheuski on 5.05.22.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKXMLModel.h>
#import <StackRendering/STKXMLVASTInLineModel.h>
#import <StackRendering/STKXMLVASTADWrapperModel.h>


@interface STKXMLVASTADInLineModel: STKXMLModel

@property (nonatomic, readonly) NSString *ID;
@property (nonatomic, readonly) NSNumber *sequence;
@property (nonatomic, readonly) STKXMLVASTInLineModel *inLine;

- (void)populateWithADWrapper:(STKXMLVASTADWrapperModel *)adWrapper;

@end
