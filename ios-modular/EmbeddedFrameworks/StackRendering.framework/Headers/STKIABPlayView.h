//
//  STKVideoPlayButton.h
//  StackVideoPlayer
//
//  Created by Stas Kochkin on 15.10.2020.
//

#import <UIKit/UIKit.h>
#import <StackRendering/STKIABAssetsDefines.h>
#import <StackRendering/STKIABViewProtocol.h>


@interface STKIABPlayView : UIView <STKIABViewProtocol>

@property (nonatomic, copy) NSString *text;
@property (nonatomic, copy) UIColor *strokeColor;
@property (nonatomic, copy) UIColor *fillColor;
@property (nonatomic, copy) UIColor *shadowColor;
@property (nonatomic, copy) UIFont *font;

@property (nonatomic, assign) CGSize size;
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, assign) BOOL outlined;
@property (nonatomic, assign) CGFloat strokeWidth;

@property (nonatomic, copy) void(^onTouchInside)(void);

- (instancetype)initWithStyle:(STKIABPlayViewStyle)style;

@end

