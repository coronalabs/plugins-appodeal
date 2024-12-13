//
//  APDXMLModel.h
//  Appodeal
//
//  Created by Lozhkin Ilya on 8/3/17.
//  Copyright © 2017 Appodeal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKXMLNode.h>


typedef id(^STKXMLTransformBlock)(STKXMLNode *node);

@interface STKXMLNodeTransformer : NSValueTransformer

/**
 Designated initializer
 
 @param block Transformation block Node -> Model
 @return instance of HBValueTransformer
 */
+ (instancetype)transformerWithBlock:(STKXMLTransformBlock)block;

/**
 Transform all child nodes to model class

 @param modelClass Class of model
 @return Transformer
 */
+ (instancetype)childNodesTransformerToModelClass:(Class)modelClass;

/**
 Transform node to current model class

 @param modelClass Model class
 @return return value transformer
 */
+ (instancetype)nodeTransformerToModelClass:(Class)modelClass;

/**
 Transform node content to array of strings

 @return Transformer
 */
+ (instancetype)nodeContentTransfomerToArrayOfStrings;

@end

/**
 Abstract XML Model implementation
 @warning Be sure that all properties has custom transformers
 It should be named as PROPERTY_NAMEValueTransformer
 */
@interface STKXMLModel : NSObject

/**
 Serialize XML data (NSFicrionary format after xml2 processing) to model

 @param node Node to parse
 @return Model
 */
+ (instancetype)modelByParsingNode:(STKXMLNode *)node;

 /**
 Map dictionary that keys contains nodeNames by value transformers path

 @return Map dictionary
 */
+ (NSDictionary <NSString *, NSString *> *)propertyPathByNodeName;
/**
Map dictionary that keys contains childNodeAttributeNames by value transformers path

@return Map dictionary
*/
+ (NSDictionary <NSString *, NSString *> *)propertyPathByChildNodeAttributeName;

@end
