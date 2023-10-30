//
//  AVPProgressBar.h
//  StackVideoPlayer
//
//  Created by Ilia Lozhkin on 1/9/19.
//

#import <UIKit/UIKit.h>
#import <StackIABAssets/STKIABAssetsDefines.h>
#import <StackIABAssets/STKIABViewProtocol.h>


@interface STKIABProgressView : UIView <STKIABViewProtocol>

@property (nonatomic, copy) NSString *text;
@property (nonatomic, copy) UIColor *strokeColor;
@property (nonatomic, copy) UIColor *fillColor;
@property (nonatomic, copy) UIColor *shadowColor;
@property (nonatomic, copy) UIFont *font;

@property (nonatomic, assign) CGSize size;
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, assign) BOOL outlined;
@property (nonatomic, assign) CGFloat strokeWidth;

- (instancetype)initWithStyle:(STKIABProgressViewStyle)style
                     duration:(NSTimeInterval)duration;

- (void)setProgress:(CGFloat)progress;

@end
