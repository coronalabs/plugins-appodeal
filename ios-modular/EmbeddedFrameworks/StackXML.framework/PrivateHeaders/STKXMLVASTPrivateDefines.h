//
//  STKXMLVASTPrivateDefines.h
//  StackXML
//
//  Created by Ilia Lozhkin on 1/16/19.
//

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLVASTDefines.h>

FOUNDATION_EXPORT BOOL const kSTKXMLVASTValidateWithSchema;

#define stk_RUN_BLOCK_ASYNC_MAIN_THREAD(block, ...) \
dispatch_async(dispatch_get_main_queue(), ^{ \
block ? block(__VA_ARGS__) : nil; \
});

extern void STKXMLVASTErrorCodeEnumeration(STKXMLVASTErrorOption, void(^)(STKXMLVASTErrorCode));
