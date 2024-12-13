//
//  STKVASTMeasureResources.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 19.08.2020.
//  Copyright © 2020 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKVASTMeasureResources : NSObject

@property(nonatomic, strong, nonnull) NSURL *URL;
@property(nonatomic, strong, nullable) NSString *vendorKey;
@property(nonatomic, strong, nullable) NSString *parameters;

@end

NS_ASSUME_NONNULL_END
