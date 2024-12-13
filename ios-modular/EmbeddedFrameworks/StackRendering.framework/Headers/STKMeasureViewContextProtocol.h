//
//  STKMeasureViewContextProtocol.h
//  StackOpenMeasure
//
//  Created by Ilia Lozhkin on 21.02.2021.
//  Copyright © 2021 Appodeal. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StackRendering/STKMeasureObstruction.h>

NS_ASSUME_NONNULL_BEGIN

@protocol STKMeasureViewContextProtocol <NSObject>

- (void)registerMainView:(UIView *)mainView;
- (void)unRegisterMainView;

- (void)registerFriendlyObstruction:(STKMeasureObstruction *)obstruction;
- (void)registerFriendlyObstructions:(NSArray<STKMeasureObstruction *> *)obstructions;

- (void)removeFriendlyObstruction:(STKMeasureObstruction *)obstruction;
- (void)removeAllFriendlyObstructions;

@end

NS_ASSUME_NONNULL_END
