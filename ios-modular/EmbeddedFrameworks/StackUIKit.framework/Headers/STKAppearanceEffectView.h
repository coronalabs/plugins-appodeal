//
//  STKAppearanceEffectView.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class STKAppearanceEffectView;

@protocol STKAppearanceEffectViewDelegate <NSObject>

- (void)effectView:(STKAppearanceEffectView *)view setAlphaControl:(CGFloat)alpha;

@end

@interface STKAppearanceEffectView : UIView

@property (nonatomic, assign) BOOL autoHideSubviews;

@property (nonatomic, weak) id<STKAppearanceEffectViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
