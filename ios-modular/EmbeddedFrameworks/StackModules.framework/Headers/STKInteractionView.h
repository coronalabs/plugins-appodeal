//
//  STKInteractionView.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 6/28/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^STKInteraction)(void);

@interface STKInteractionView <ObjectType> : UIView

@property (nonatomic, strong, nullable) ObjectType contentView;

- (void)addContentInsent:(UIEdgeInsets)inset;

- (void)addTarget:(id)target action:(SEL)action;

- (void)addInteraction:(STKInteraction)interaction;

@end

NS_ASSUME_NONNULL_END
