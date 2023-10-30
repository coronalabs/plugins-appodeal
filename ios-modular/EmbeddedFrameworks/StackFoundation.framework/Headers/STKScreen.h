//
//  STKScreen.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STKScreen : NSObject

@property (class, nonatomic, readonly) float width;

@property (class, nonatomic, readonly) float height;

@property (class, nonatomic, readonly) float ppi;

@property (class, nonatomic, readonly) float ratio;

@end

NS_ASSUME_NONNULL_END
