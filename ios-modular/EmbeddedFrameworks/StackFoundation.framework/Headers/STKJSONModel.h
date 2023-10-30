//
//  STKJSONModel.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKJSONSerializable <NSObject>

+ (NSDictionary <NSString *, NSString *>*)JSONKeyByPropertyMap;

+ (nullable instancetype)modelFromJSON:(NSDictionary <NSString *, id>*)JSONDictionary;

+ (nullable instancetype)modelFromJSONData:(NSData *)JSONData error:(NSError **)error;

+ (nullable instancetype)modelFromJSON:(NSDictionary <NSString *, id>*)JSONDictionary error:(NSError **)error;

- (NSDictionary <NSString *, id>*)JSONRepresentation;

@optional

+ (NSValueTransformer *)valueTransformer; //+ (NSValueTransformer *)propertyName_valueTransforemer {}

@end


@interface STKJSONModel : NSObject <STKJSONSerializable>

@end

NS_ASSUME_NONNULL_END
