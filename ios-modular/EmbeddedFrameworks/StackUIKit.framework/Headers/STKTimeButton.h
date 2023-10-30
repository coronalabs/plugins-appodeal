//
//  STKTimeButton.h
//  StackUIKit
//
//  Created by Ilia Lozhkin on 7/1/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <StackUIKit/STKCoreButton.h>

@interface STKTimeButton : STKCoreButton

- (void)updatePercent:(float)percent timeValue:(unsigned int)timeValue;

@end
