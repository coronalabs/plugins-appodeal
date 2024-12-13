//
//  STKIABLayoutConstraint.h
//  StackIABAssets
//
//  Created by Stas Kochkin on 09.12.2020.
//

#import <Foundation/Foundation.h>
#import <StackRendering/STKIABAssetsDefines.h>
#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

@interface STKIABLayoutConstraint : NSObject

+ (void)layoutView:(UIView *)view
         superview:(UIView *)superview
horizontalPosition:(STKIABAssetHorizontalPosition)horizontalPosition
  verticalPosition:(STKIABAssetVerticalPosition)verticalPosition
useSafeAreaLayoutGuide:(BOOL)useSafeAreaLayoutGuide
           margins:(UIEdgeInsets)margins;

+ (void)activateHorizontalConstaint:(STKIABAssetHorizontalPosition)position
                         targetView:(UIView *)targetView
                          container:(UIView *)container
             useSafeAreaLayoutGuide:(BOOL)useSafeAreaLayoutGuide
                             offset:(CGFloat)offset;

+ (void)activateVerticalConstaint:(STKIABAssetVerticalPosition)position
                       targetView:(UIView *)targetView
                        container:(UIView *)container
           useSafeAreaLayoutGuide:(BOOL)useSafeAreaLayoutGuide
                           offset:(CGFloat)offset;

@end

NS_ASSUME_NONNULL_END
