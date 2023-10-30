//
//  STKVASTAssetDefines.h
//  StackVASTAssets
//
//  Created by Ilia Lozhkin on 12/19/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


FOUNDATION_EXPORT NSString *kSTKIABControlDefaultFillColor;

FOUNDATION_EXPORT NSString *kSTKIABCTAViewStyleDefault;

FOUNDATION_EXPORT NSString *kSTKIABMuteViewStyleSpeaker;
FOUNDATION_EXPORT NSString *kSTKIABMuteViewStyleSpeakerFill;

FOUNDATION_EXPORT NSString *kSTKIABClosableViewStyleCross;
FOUNDATION_EXPORT NSString *kSTKIABClosableViewStyleSkip;

FOUNDATION_EXPORT NSString *kSTKIABProgressViewStyleLinear;
FOUNDATION_EXPORT NSString *kSTKIABProgressViewStyleCircular;
FOUNDATION_EXPORT NSString *kSTKIABProgressViewStyleCircularReverse;
FOUNDATION_EXPORT NSString *kSTKIABProgressViewStyleText;

FOUNDATION_EXPORT NSString *kSTKIABCountdownViewStyleCircular;
FOUNDATION_EXPORT NSString *kSTKIABCountdownViewStyleText;

FOUNDATION_EXPORT NSString *kSTKIABRepeatViewStylePlay;

FOUNDATION_EXPORT NSString *kSTKIABForceOrientationPortrait;

CGSize STKIABAssetSize(void);
UIEdgeInsets STKIABDefaultInsets(void);
UIColor *STKIABDefaultFillColor(void);
UIColor *STKIABDefaultStrokeColor(void);
UIColor *STKIABDefaultShadowColor(void);

FOUNDATION_EXPORT CGFloat kSTKIABAssetLineWidth;
FOUNDATION_EXPORT CGFloat kSTKIABAssetShadowRadius;

/**
 Creative size

 - STKIABAssetAspectRatioUnknown: Crative size undefined
 - STKIABAssetAspectRatioBanner: Creative size equal 320*50 or 728*90
 - STKIABAssetAspectRatioLandscape: Creative size near for device landscape size
 - STKIABAssetAspectRatioPortrait: Creative size near for device portrait size
 */
typedef NS_ENUM(NSInteger, STKIABAssetAspectRatio) {
    STKIABAssetAspectRatioUnknown = 0,
    STKIABAssetAspectRatioBanner,
    STKIABAssetAspectRatioLandscape,
    STKIABAssetAspectRatioPortrait
};
/**
 Horizontal postion of control asset

 - STKIABAssetHorizontalPositionLeft: Left corner of screen
 - STKIABAssetHorizontalPositionRight: Right corner of screen
 - STKIABAssetHorizontalPositionCenter: Center of screen
 */
typedef NS_ENUM(NSInteger, STKIABAssetHorizontalPosition) {
    STKIABAssetHorizontalPositionLeft = 0,
    STKIABAssetHorizontalPositionRight,
    STKIABAssetHorizontalPositionCenter
};
/**
 Vertical postion of control asset

 - STKIABAssetVerticalPositionTop: Top of screen
 - STKIABAssetVerticalPositionBottom: Top of screen
 - STKIABAssetVerticalPositionCenter: Center of screen
 */
typedef NS_ENUM(NSInteger, STKIABAssetVerticalPosition) {
    STKIABAssetVerticalPositionTop = 0,
    STKIABAssetVerticalPositionBottom,
    STKIABAssetVerticalPositionCenter
};

typedef NS_ENUM(NSUInteger, STKIABClosableViewStyle) {
    STKIABClosableViewStyleCross = 0,
    STKIABClosableViewStyleSkip,
};

STKIABClosableViewStyle STKIABClosableViewStyleFromString(NSString *string);

typedef NS_ENUM(NSInteger, STKIABForceOrientation) {
    STKIABForceOrientationPortrait = 0,
    STKIABForceOrientationLandscape,
    STKIABForceOrientationNone
};

STKIABForceOrientation STKIABForceOrientationFromString(NSString *string);

typedef NS_ENUM(NSUInteger, STKIABMuteViewStyle) {
    STKIABMuteViewStyleSpeaker = 0,
    STKIABMuteViewStyleSpeakerfill
};

STKIABMuteViewStyle STKIABMuteViewStyleFromString(NSString *string);

typedef NS_ENUM(NSUInteger, STKIABProgressViewStyle) {
    STKIABProgressViewStyleLinear = 0,
    STKIABProgressViewStyleCircular,
    STKIABProgressViewStyleCircularReverse,
    STKIABProgressViewStyleText
};

STKIABProgressViewStyle STKIABProgressViewStyleFromString(NSString *string);

typedef NS_ENUM(NSUInteger, STKIABCountdownViewStyle) {
    STKIABCountdownViewStyleCircular = 0,
    STKIABCountdownViewStyleText,
};

STKIABCountdownViewStyle STKIABCountdownViewStyleFromString(NSString *string);

typedef NS_ENUM(NSUInteger, STKIABCallToActionViewStyle) {
    STKIABCallToActionViewStyleDefault = 0
};

STKIABCallToActionViewStyle STKIABCallToActionViewStyleFromString(NSString *string);

typedef NS_ENUM(NSUInteger, STKIABPlayViewStyle) {
    STKIABPlayViewStyleDefault = 0,
    STKIABPlayViewStyleFill
};

STKIABPlayViewStyle STKIABPlayViewStyleFromString(NSString *string);

UIEdgeInsets UIEdgeInsetsFromSTKIABString(NSString *string, UIEdgeInsets defaultValue);
UIFont *UIFontFromSTKIABFontStyleString(NSString *string);
UIColor *UIColorFromSTKIABString(NSString *string, UIColor *defaultColor);
CGSize CGSizeFromSTKIABSize(NSString *width, NSString *height, CGSize defaultSize);
STKIABAssetHorizontalPosition STKIABAssetHorizontalPositionFromSTKIABString(NSString *string, STKIABAssetHorizontalPosition defaultPosition);
STKIABAssetVerticalPosition STKIABAssetVerticalPositionFromSTKIABString(NSString *string, STKIABAssetVerticalPosition defaultPosition);
