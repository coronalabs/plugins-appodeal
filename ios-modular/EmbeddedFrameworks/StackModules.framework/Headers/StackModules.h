//
//  StackFoundation.h
//  StackFoundation
//
//  Created by Lozhkin Ilya on 3/16/18.
//  Copyright © 2019 Stack. All rights reserved.
//

#define STK_RUN_BLOCK(block, ...)                   block ? block(__VA_ARGS__) : nil

#define STK_SET_AUTORELASE_VAR(Var, Value)          if (Var != NULL) { *Var = Value; }

#import <UIKit/UIKit.h>

#import <StackModules/STKFoundationDefines.h>
#import <StackModules/STKDevice.h>
#import <StackModules/STKInterface.h>
#import <StackModules/STKScreen.h>
#import <StackModules/STKBundle.h>
#import <StackModules/STKAd.h>
#import <StackModules/STKConnection.h>
#import <StackModules/STKLocation.h>

#import <StackModules/STKAny.h>
#import <StackModules/STKError.h>
#import <StackModules/STKBoxStorage.h>
#import <StackModules/STKLocationManager.h>
#import <StackModules/STKNetworkSession.h>
#import <StackModules/STKTimer.h>
#import <StackModules/STKExpirationTimer.h>
#import <StackModules/STKNetworkReachability.h>
#import <StackModules/STKThirdPartyEventTracker.h>
#import <StackModules/STKCryptoVerificaton.h>
#import <StackModules/STKEncryptionKeyProtocol.h>
#import <StackModules/STKRSAKey.h>
#import <StackModules/STKECCKey.h>
#import <StackModules/STKGenerator.h>
#import <StackModules/STKOperation.h>
#import <StackModules/STKObjectCacher.h>
#import <StackModules/STKFile.h>
#import <StackModules/STKDirectory.h>
#import <StackModules/STKDataCacher.h>
#import <StackModules/STKJSONModel.h>
#import <StackModules/STKJSONSerialization.h>
#import <StackModules/STKValueTransformer.h>
#import <StackModules/STKLogger.h>
#import <StackModules/STKLoggerDefines.h>
#import <StackModules/STKNativeLogRecorder.h>
#import <StackModules/STKSystemLogRecorder.h>
#import <StackModules/STKContainerLogRecorder.h>
#import <StackModules/STKStorageLogRecorder.h>
#import <StackModules/STKStreamingLogRecorder.h>

#import <StackModules/NSObject+STKFoundation.h>
#import <StackModules/NSURL+STKFoundation.h>
#import <StackModules/NSArray+STKFoundation.h>
#import <StackModules/NSDate+STKFoundation.h>
#import <StackModules/NSData+STKFoundation.h>
#import <StackModules/NSString+STKFoundation.h>
#import <StackModules/NSFileManager+STKFoundation.h>

#import <StackModules/STKUIDefines.h>
#import <StackModules/STKInteractionView.h>
#import <StackModules/STKRotationController.h>
#import <StackModules/STKAppearanceEffectView.h>
#import <StackModules/STKSpinnerView.h>
#import <StackModules/STKSpinnerScreen.h>
#import <StackModules/STKSpinnerWindow.h>
#import <StackModules/STKSpinnerViewController.h>
#import <StackModules/STKCoreButton.h>
#import <StackModules/STKCoreButtonSettings.h>
#import <StackModules/STKCoreButtonSettingsBuilder.h>
#import <StackModules/STKMuteButton.h>
#import <StackModules/STKPlayButton.h>
#import <StackModules/STKRepeatButton.h>
#import <StackModules/STKTextButton.h>
#import <StackModules/STKTimeButton.h>
#import <StackModules/STKCloseButton.h>
#import <StackModules/STKCircleTimerButton.h>
#import <StackModules/STKViewabilityTracker.h>
#import <StackModules/STKLayout.h>
#import <StackModules/STKLayoutBuilder.h>
#import <StackModules/UIView+STKLayout.h>
#import <StackModules/STKLayoutGuide.h>
#import <StackModules/STKSafeAreaLayoutGuide.h>
#import <StackModules/STKLayoutDimension.h>
#import <StackModules/STKLayoutConstraint.h>
#import <StackModules/STKLayoutGuide+STKLayout.h>

#import <StackModules/UIView+STKUIKit.h>
#import <StackModules/UIView+STKViewability.h>
#import <StackModules/UIApplication+STKUIKit.h>
#import <StackModules/UIColor+STKUIKit.h>
#import <StackModules/UIImage+STKUIKit.h>
#import <StackModules/UIViewController+STKUIKit.h>
#import <StackModules/UIImageView+STKUIKit.h>

//! Project version number for StackFoundation.
FOUNDATION_EXPORT double StackFoundationVersionNumber;

//! Project version string for StackFoundation.
FOUNDATION_EXPORT const unsigned char StackFoundationVersionString[];


