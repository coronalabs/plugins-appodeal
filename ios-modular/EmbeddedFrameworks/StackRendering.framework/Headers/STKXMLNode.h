//
//  STKXMLNode.h
//  StackXML
//
//  Created by Stas Kochkin on 03/11/2017.
//  Copyright © 2017 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface STKXMLAttribute : NSObject

@property (nonatomic, readonly, copy) NSString *name;
@property (nonatomic, readonly, copy) NSString *content;
@property (nonatomic, readonly, assign) BOOL valid;

//+ (instancetype)attributeFromDictionary:(NSDictionary *)attributeDictionary;

@end


@interface STKXMLNode : STKXMLAttribute

@property (nonatomic, readonly, copy) NSArray <STKXMLNode *> *childNodes;
@property (nonatomic, readonly, copy) NSArray <STKXMLAttribute *> *attributes;

// Handling <CDATA>
- (NSString *)searchContent;

//+ (instancetype)nodeFromDictionary:(NSDictionary *)nodeDictionary;
- (void)performRecursiveSearch:(void(^)(STKXMLNode *node))searchBlock;
- (STKXMLNode *)searchNodeWithName:(NSString *)name;

@end

@interface STKXMLNode (Private)

@property (nonatomic, readwrite, copy) NSString *name;
@property (nonatomic, readwrite, copy) NSArray <STKXMLNode *> *childNodes;
@property (nonatomic, readwrite, copy) NSArray <STKXMLAttribute *> *attributes;
@property (nonatomic, readwrite, copy) NSString *content;

@end

@interface STKXMLAttribute (Private)

@property (nonatomic, readwrite, copy) NSString *name;
@property (nonatomic, readwrite, copy) NSString *content;

@end

