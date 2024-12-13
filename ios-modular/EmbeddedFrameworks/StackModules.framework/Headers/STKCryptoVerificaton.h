//
//  STKCertificateValidator.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, STKValidationResult){
    STKValidationResultInvalidParamter = 0,
    STKValidationResultError,
    STKValidationResultCertifiacteUntrasted,
    STKValidationResultCertificateTrusted
};

/// Signaturre algotirhm
/// - STKSignatureAlgorithmRSA: RSA signature PKCS1v15 SHA256
/// - STKSignatureAlgorithmECDSA: ECDSA Signature X9.62 SHA256
typedef NS_ENUM(NSInteger, STKSignatureAlgorithm) {
    STKSignatureAlgorithmRSA = 0,
    STKSignatureAlgorithmECDSA
};

@interface STKCryptoVerificaton : NSObject
/// Validate certificate chain trust for given host
/// @param trustRef Certifiacte chain trust reference
/// @param host Host
/// @param pinnedKeysHashes Trusted hashes of pinned keys
+ (STKValidationResult)validateCertificateTrust:(SecTrustRef)trustRef
                                           host:(NSString *)host
                               pinnedKeysHashes:(NSSet <NSString *> *)pinnedKeysHashes;

/// Validate signature
/// @param signature Signature data
/// @param algorithm Signature algorithm
/// @param publicKey Public key reference
/// @param message Raw message
+ (BOOL)isValidSignature:(NSData *)signature
               algorithm:(STKSignatureAlgorithm)algorithm
               publicKey:(SecKeyRef)publicKey
                 message:(NSData *)message API_AVAILABLE(ios(10));
@end

NS_ASSUME_NONNULL_END
