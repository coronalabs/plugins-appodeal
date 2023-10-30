//
//  StackFoundation.h
//  StackFoundation
//
//  Created by Lozhkin Ilya on 3/16/18.
//  Copyright © 2019 Stack. All rights reserved.
//

#define STK_RUN_BLOCK(block, ...)                   block ? block(__VA_ARGS__) : nil

#define STK_SET_AUTORELASE_VAR(Var, Value)          if (Var != NULL) { *Var = Value; }

#import <StackFoundation/STKFoundationDefines.h>
#import <StackFoundation/STKDevice.h>
#import <StackFoundation/STKInterface.h>
#import <StackFoundation/STKScreen.h>
#import <StackFoundation/STKBundle.h>
#import <StackFoundation/STKAd.h>
#import <StackFoundation/STKConnection.h>
#import <StackFoundation/STKLocation.h>

#import <StackFoundation/STKAny.h>
#import <StackFoundation/STKError.h>
#import <StackFoundation/STKBoxStorage.h>
#import <StackFoundation/STKLocationManager.h>
#import <StackFoundation/STKNetworkSession.h>
#import <StackFoundation/STKTimer.h>
#import <StackFoundation/STKExpirationTimer.h>
#import <StackFoundation/STKNetworkReachability.h>
#import <StackFoundation/STKThirdPartyEventTracker.h>
#import <StackFoundation/STKCryptoVerificaton.h>
#import <StackFoundation/STKEncryptionKeyProtocol.h>
#import <StackFoundation/STKRSAKey.h>
#import <StackFoundation/STKECCKey.h>
#import <StackFoundation/STKGenerator.h>
#import <StackFoundation/STKOperation.h>
#import <StackFoundation/STKObjectCacher.h>
#import <StackFoundation/STKFile.h>
#import <StackFoundation/STKDirectory.h>
#import <StackFoundation/STKDataCacher.h>
#import <StackFoundation/STKJSONModel.h>
#import <StackFoundation/STKJSONSerialization.h>
#import <StackFoundation/STKValueTransformer.h>
#import <StackFoundation/STKLogger.h>
#import <StackFoundation/STKLoggerDefines.h>
#import <StackFoundation/STKNativeLogRecorder.h>
#import <StackFoundation/STKSystemLogRecorder.h>
#import <StackFoundation/STKContainerLogRecorder.h>
#import <StackFoundation/STKStorageLogRecorder.h>
#import <StackFoundation/STKStreamingLogRecorder.h>

#import <StackFoundation/NSObject+STKFoundation.h>
#import <StackFoundation/NSURL+STKFoundation.h>
#import <StackFoundation/NSArray+STKFoundation.h>
#import <StackFoundation/NSDate+STKFoundation.h>
#import <StackFoundation/NSData+STKFoundation.h>
#import <StackFoundation/NSString+STKFoundation.h>
#import <StackFoundation/NSFileManager+STKFoundation.h>

//! Project version number for StackFoundation.
FOUNDATION_EXPORT double StackFoundationVersionNumber;

//! Project version string for StackFoundation.
FOUNDATION_EXPORT const unsigned char StackFoundationVersionString[];


