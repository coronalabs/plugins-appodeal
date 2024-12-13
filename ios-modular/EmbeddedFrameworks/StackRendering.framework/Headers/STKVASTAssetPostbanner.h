//
//  STKVASTAssetPostbanner.h
//  StackVASTAssets
//
//  Created by Stas Kochkin on 15.12.2020.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKIABAsset.h>
#import <StackRendering/STKXMLVASTPostbannerExtensionModel.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKVASTAssetPostbanner : NSObject <NSCopying>

@property (nonatomic, assign, readonly) BOOL useCustomClose;
@property (nonatomic, assign, readonly) BOOL r1;
@property (nonatomic, assign, readonly) BOOL r2;
@property (nonatomic, assign, readonly) BOOL ignoresSafeAreaLayoutGuide;

@property (nonatomic, assign, readonly) NSTimeInterval closeTime;
@property (nonatomic, assign, readonly) NSTimeInterval duration;

@property (nonatomic, copy, readonly) STKIABAsset *countdownAsset;
@property (nonatomic, copy, readonly) STKIABAsset *closableViewAsset;
@property (nonatomic, copy, readonly) STKIABAsset *progressAsset;

@property (nonatomic, copy, readonly, nullable) NSString *productLink;


- (instancetype)initWithPostbannerExtension:(STKXMLVASTPostbannerExtensionModel *)postbannerExtension;

@end

NS_ASSUME_NONNULL_END
