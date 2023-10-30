//
//  STKVASTAssetOMVerification.h
//  StackVASTAssets
//
//  Created by Ilia Lozhkin on 1/31/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAssetOMVerification : NSObject

@property(nonatomic, strong, nonnull) NSURL *URL;
@property(nonatomic, strong, nullable) NSString *vendorKey;
@property(nonatomic, strong, nullable) NSString *parameters;

@end

NS_ASSUME_NONNULL_END
