//
//  STKIABViewProtocol.h
//  StackIABAssets
//
//  Created by Stas Kochkin on 22.12.2020.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

@protocol STKIABViewProtocol <NSObject>

@property (nonatomic, copy, readwrite) UIColor *strokeColor;
@property (nonatomic, copy, readwrite) UIColor *fillColor;
@property (nonatomic, copy, readwrite) UIColor *shadowColor;
@property (nonatomic, copy, readwrite) UIFont *font;

@property (nonatomic, assign, readwrite) CGSize size;
@property (nonatomic, assign, readwrite) UIEdgeInsets insets;
@property (nonatomic, assign, readwrite) BOOL outlined;
@property (nonatomic, assign, readwrite) CGFloat strokeWidth;

@end

NS_ASSUME_NONNULL_END
