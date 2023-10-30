//
//  STKConsentManagerJSONModel.h
//  StackConsentManager
//
//  Created by Stas Kochkin on 20.12.2019.
//  Copyright © 2019 com.stasko. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol STKConsentManagerJSONModel <NSObject>

+ (instancetype)modelFromJsonDictionary:(NSDictionary <NSString *, id>*)jsonDictionary;
- (NSDictionary <NSString *, id> *)JSONRepresentation;

@end
