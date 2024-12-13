//
//  AMKPresentationConfiguration.h
//
//  Copyright © 2019 Appodeal. All rights reserved.
//

#import <UIKit/UIKit.h>

@class STKIABAsset;

typedef NS_ENUM(NSInteger, STKMRAIDContentMode) {
    STKMRAIDContentModeFit = 0,
    STKMRAIDContentModeFill
};

NS_ASSUME_NONNULL_BEGIN

@interface STKMRAIDPresentationConfiguration : NSObject <NSCopying>

@property (nonatomic, assign) NSTimeInterval closeTime;
@property (nonatomic, assign) NSTimeInterval placeholderTime;
@property (nonatomic, assign) NSTimeInterval duration;

@property (nonatomic, assign) BOOL useNativeClose;
@property (nonatomic, assign) BOOL r1;
@property (nonatomic, assign) BOOL r2;
@property (nonatomic, assign) BOOL ignoresSafeAreaLayout;
@property (nonatomic, assign) BOOL isSpinnerActive;
@property (nonatomic, assign) BOOL isOverlayActive;
@property (nonatomic, assign) NSTimeInterval r1Delay;
@property (nonatomic, assign) STKMRAIDContentMode contentMode;

@property (nonatomic, copy, nullable) NSString *productLink;
@property (nonatomic, copy, nullable) UIColor *backgroundColor;

@property (nonatomic, copy) STKIABAsset *countdownAsset;
@property (nonatomic, copy) STKIABAsset *closableAsset;
@property (nonatomic, copy) STKIABAsset *progressAsset;

@property (nonatomic, copy, nullable) NSDictionary <NSString *, id> *productParameters;

@end

NS_ASSUME_NONNULL_END
