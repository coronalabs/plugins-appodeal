//
//  STKEncryptionKeyProtocol.h
//  StackFoundation
//
//  Created by Stas Kochkin on 30.03.2020.
//  Copyright © 2020 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKEncryptionKey <NSObject>
/// Raw base64 key representation
@property (nonatomic, copy, readonly) NSString *base64Encoded;
/// Supports PKSC 8 PEM key format
/// @param pem Raw pem string
- (instancetype)initWithPem:(NSString *)pem;
/// Supports PKSC 8 PEM key format
/// @param base64EncodedString Base64 string
- (instancetype)initWithBase64EncodedString:(NSString *)base64EncodedString;
/// Public key reference
/// @param error Error object that returned in case create from data failed
- (nullable SecKeyRef)publicKeyReferenceWithError:(NSError **)error API_AVAILABLE(ios(10));
/// Private key reference
/// @param error Error object that returned in case create from data failed
- (nullable SecKeyRef)privateKeyReferenceWithError:(NSError **)error API_AVAILABLE(ios(10));
@end

NS_ASSUME_NONNULL_END
