//
//  STKRSAKey.h
//  StackFoundation
//
//  Created by Stas Kochkin on 30.03.2020.
//  Copyright © 2020 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StackModules/STKEncryptionKeyProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/// RSA key wrapper
@interface STKRSAKey : NSObject <STKEncryptionKey>
@end

NS_ASSUME_NONNULL_END
