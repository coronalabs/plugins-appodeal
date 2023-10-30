//
//  VASTXMLUtil.h
//  VAST
//
//  Created by Jay Tucker on 10/15/13.
//  Copyright (c) 2013 Nexage. All rights reserved.
//
//  VASTXMLUtil validates a VAST document for correct XML syntax and conformance to the VAST 2.0.1.xsd schema.

#import <Foundation/Foundation.h>
#import <StackXML/STKXMLNode.h>

BOOL STKXMLVASTIsValidXMLDocument(NSData *document);                         // check for valid XML syntax using xmlReadMemory
BOOL STKXMLVASTIsValidXMLDocumentAgainstSchema(NSData *document, NSData *schema);  // check for valid VAST 2.0 syntax using xmlSchemaValidateDoc & vast_2.0.1.xsd schema
STKXMLNode *STKXMLVASTPerformXMLNodeSearch(NSData *document, NSString *name);    // parse the document for the xpath in 'query' using xmlXPathEvalExpression
STKXMLNode *STKXMLVASTPerformXMLRootNode(NSData *document);
