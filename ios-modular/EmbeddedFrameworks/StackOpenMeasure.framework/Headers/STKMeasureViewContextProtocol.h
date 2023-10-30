//
//  STKMeasureViewContextProtocol.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 21.02.2021.
//  Copyright © 2021 Appodeal. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKMeasureViewContextProtocol <NSObject>

- (void)registerMainView:(UIView *)mainView;
- (void)registerFriendlyObstruction:(UIView *)view;
- (void)registerFriendlyObstructions:(NSArray<UIView *> *)views;

@end

NS_ASSUME_NONNULL_END
