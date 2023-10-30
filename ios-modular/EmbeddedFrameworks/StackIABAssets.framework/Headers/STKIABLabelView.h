//
//  STKLabelView.h
//  StackVideoPlayer
//
//  Created by Stas Kochkin on 23.10.2020.
//

#import <UIKit/UIKit.h>
#import <StackIABAssets/STKIABViewProtocol.h>


@interface STKIABLabelView : UIView <STKIABViewProtocol>

@property (nonatomic, copy) NSString *text;
@property (nonatomic, copy) UIColor *strokeColor;
@property (nonatomic, copy) UIColor *fillColor;
@property (nonatomic, copy) UIColor *shadowColor;
@property (nonatomic, copy) UIFont *font;

@property (nonatomic, assign) CGSize size;
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, assign) BOOL outlined;
@property (nonatomic, assign) CGFloat strokeWidth;

- (instancetype)init;

@end
