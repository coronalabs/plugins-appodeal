//
//  NSData+STKFoundation.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSData (STKZipper)

- (NSData *_Nullable)stk_gzipCompressedDataWithError:(NSError **_Nullable)error;

- (NSData *_Nullable)stk_gzipDecompressedDataWithError:(NSError **_Nullable)error;

- (void)stk_gzipCompressedDataAsync:(void(^)(NSData *_Nullable, NSError *_Nullable))completion;

- (void)stk_gzipDecompressedDataAsync:(void(^)(NSData *_Nullable, NSError *_Nullable))completion;

@end

@interface NSData (STKCrypto)

@property (nonatomic, copy, readonly) NSString *stk_SHA256HEXUppercased;

+ (NSData *)stk_random128BitVector;

+ (NSData *_Nullable)stk_dataFromSecKeyRef:(SecKeyRef)keyRef;

- (NSData *_Nullable)stk_AESPKCS7PaddingEncryptedDataWithKey:(NSData *)key
                                      initialVector:(NSData *)initialVector;

- (NSString *)stk_base32EncodedString;

+ (NSData *)stk_dataWithBase32String:(NSString*)base32String;

@end

@interface NSData (STKImageRef)

- (CGImageRef _Nullable)stk_imageRef:(int)size;

@end

NS_ASSUME_NONNULL_END
