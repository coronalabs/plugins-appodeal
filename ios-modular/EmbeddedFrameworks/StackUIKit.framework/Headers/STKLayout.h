//
//  STKLayout.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLayout : NSObject

@property (nonatomic, readonly) STKLayout *(^equal)(id _Nullable);
@property (nonatomic, readonly) STKLayout *(^lessThanOrEqual)(id _Nullable);
@property (nonatomic, readonly) STKLayout *(^greaterThanOrEqual)(id _Nullable);

@property (nonatomic, readonly) STKLayout *with;

@property (nonatomic, readonly) STKLayout *(^offset)(CGFloat);
@property (nonatomic, readonly) STKLayout *(^multiplier)(CGFloat);

@end

NS_ASSUME_NONNULL_END
