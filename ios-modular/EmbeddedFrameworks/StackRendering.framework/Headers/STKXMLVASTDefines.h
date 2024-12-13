//
//  STKXMLVASTDefines.h
//  StackXML
//
//  Created by Ilia Lozhkin on 1/16/19.
//

#ifndef STKXMLVASTDefines_h
#define STKXMLVASTDefines_h

typedef NS_ENUM(NSInteger, STKXMLVASTErrorCode) {
    STKXMLVASTNoError = 0,
    STKXMLVASTParsingError = 100,                  // VAST Parsing error (document == nil || xmlDocument == nil)
    STKXMLVASTValidationError = 101,               // VAST Validation error (xmlDocument.tag != vast)
    STKXMLVASTExpectedDurationError = 202,         // VAST Video duration not compatible
    STKXMLVASTGeneralWrapperError = 300,           // VAST Wrapper error (wrapper.attribute)
    STKXMLVASTURIConnectionError = 301,            // VAST Network error (wrapper.URI == nil, wrapper.response.error)
    STKXMLVASTWrapperDeepError = 302,              // VAST Wrapper capacity (wrapper <= maxWrapperCount)
    STKXMLVASTWrapperNoAdsResponseError = 303,     // VAST No Ad (wrapper.response.code == 204, wrapper.ad.count == 0)
    STKXMLVASTNoFileError = 401,                   // VAST No file (inLine == nil)
    STKXMLVASTNoValidFileAttributeError = 403,     // VAST No Required attribute (media.requiredFields is empty)
    STKXMLVASTProblemFileError = 405,              // VAST Problec file (MIME_TYPE not supported)
    STKXMLVASTCompanionError = 600,                // VAST Postbanner companion error (companion.postbanner.count == nil)
    STKXMLVASTUndefinedError = 900                 // VAST Undefined error
};

typedef NS_OPTIONS(NSUInteger, STKXMLVASTErrorOption) {
    STKXMLVASTParsingErrorOption                   = 1 << 0,
    STKXMLVASTValidationErrorOption                = 1 << 1,
    STKXMLVASTExpectedDurationErrorOption          = 1 << 2,
    STKXMLVASTGeneralWrapperErrorOption            = 1 << 3,
    STKXMLVASTURIConnectionErrorOption             = 1 << 4,
    STKXMLVASTWrapperDeepErrorOption               = 1 << 5,
    STKXMLVASTWrapperNoAdsResponseErrorOption      = 1 << 6,
    STKXMLVASTNoFileErrorOption                    = 1 << 7,
    STKXMLVASTNoValidFileAttributeErrorOption      = 1 << 8,
    STKXMLVASTProblemFileErrorOption               = 1 << 9,
    STKXMLVASTCompanionErrorOption                 = 1 << 10,
    STKXMLVASTUndefinedErrorOption                 = 1 << 11
};

#endif /*STKXMLVASTDefines_h */
