//
//  STKRSAPublicKey.h
//  StackFoundation
//
//  Created by Stas Kochkin on 20.03.2020.
//  Copyright © 2020 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackFoundation/STKEncryptionKeyProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/// ECDSA key wrapper
/// Supported curve is prime256v1/secp384k1
@interface STKECCKey : NSObject <STKEncryptionKey>
/// Raw base64 key representation
@property (nonatomic, copy, readonly) NSString *base64Encoded;
/// Supports PKSC 8 PEM key format
/// @param pem Raw pem string
- (instancetype)initWithPem:(NSString *)pem;
/// Supports PKSC 8 PEM key format
/// @param base64EncodedString Base64 string
- (instancetype)initWithBase64EncodedString:(NSString *)base64EncodedString;
- (nullable SecKeyRef)publicKeyReferenceWithError:(NSError **)error API_AVAILABLE(ios(10));
- (nullable SecKeyRef)privateKeyReferenceWithError:(NSError **)error API_AVAILABLE(ios(10));
@end

NS_ASSUME_NONNULL_END
