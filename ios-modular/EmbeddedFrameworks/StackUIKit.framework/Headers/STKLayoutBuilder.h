//
//  STKLayoutBuilder.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackUIKit/STKLayout.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKLayoutBuilder : NSObject

@property (nonatomic, readonly) STKLayout *left;
@property (nonatomic, readonly) STKLayout *right;
@property (nonatomic, readonly) STKLayout *top;
@property (nonatomic, readonly) STKLayout *bottom;
@property (nonatomic, readonly) STKLayout *leading;
@property (nonatomic, readonly) STKLayout *trailing;
@property (nonatomic, readonly) STKLayout *width;
@property (nonatomic, readonly) STKLayout *height;
@property (nonatomic, readonly) STKLayout *centerX;
@property (nonatomic, readonly) STKLayout *centerY;
@property (nonatomic, readonly) STKLayout *lastBaseline;
@property (nonatomic, readonly) STKLayout *firstBaseline;

@end

NS_ASSUME_NONNULL_END
