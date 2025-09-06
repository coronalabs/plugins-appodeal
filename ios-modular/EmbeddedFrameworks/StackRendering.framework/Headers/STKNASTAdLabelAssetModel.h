//
//  STKNASTAdLabelAssetModel.h
//  StackRendering
//
//  Created by Eugene Marchukevich on 18/12/2024.
//  Copyright © 2024 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface STKNASTAdLabelAssetModel: NSObject

@property (strong, nonatomic, readonly, nullable) NSString *content;
@property (strong, nonatomic, readonly, nullable) NSNumber *width;
@property (strong, nonatomic, readonly, nullable) NSNumber *height;
@property (strong, nonatomic, readonly, nullable) NSNumber *position;

- (id _Nonnull )initWithContent:(NSString *_Nullable)content width:(NSNumber *_Nullable)width height:(NSNumber *_Nullable)height position:(NSNumber *_Nullable)position;

@end

