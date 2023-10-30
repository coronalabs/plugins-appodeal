//
//  AMKMessageHandler.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <WebKit/WebKit.h>

@protocol STKScriptMessageHandler <WKScriptMessageHandler>

@property (nonatomic, readonly) NSString *name;

@end
