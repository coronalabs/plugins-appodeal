//
//  STKInterface.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/27/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKInterface : NSObject

@property (class, nonatomic, readonly) UIUserInterfaceIdiom type;

@property (class, nonatomic, readonly) UIInterfaceOrientation orientation;

@property (class, nonatomic, readonly) UIEdgeInsets safeArea;

@property (class, nonatomic, readonly) CGRect deviceSize;

@property (class, nonatomic, readonly) CGFloat statusBarHeight;

@property (class, nonatomic, readonly) CGRect interfaceSize;

@property (class, nonatomic, readonly) BOOL safeAreaUntrasted;

@property (class, nonatomic, readonly) NSString *style;

@end

NS_ASSUME_NONNULL_END
