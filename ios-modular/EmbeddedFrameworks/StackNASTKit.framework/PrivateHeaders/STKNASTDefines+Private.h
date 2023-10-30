//
//  STKNASTDefines+Private.h
//  StackNASTKit
//
//  Created by Lozhkin Ilya on 5/31/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <StackNASTKit/StackNASTKit.h>

static inline NSDictionary <NSNumber *, NSNumber *> * STKNASTDefaultAssetComparator(void) {
    return @{
        @(STKNASTAssetTitle)          : @(STKNASTAssetTitle),
        @(STKNASTAssetImage)          : @(STKNASTAssetImage),
        @(STKNASTAssetIcon)           : @(STKNASTAssetIcon),
        @(STKNASTAssetVideo)          : @(STKNASTAssetVideo),
        @(STKNASTAssetDescription)    : @(STKNASTAssetDescription),
        @(STKNASTAssetRating)         : @(STKNASTAssetRating),
        @(STKNASTAssetCta)            : @(STKNASTAssetCta),
        @(STKNASTAssetNotFound)       : @(STKNASTAssetNotFound)
    };
}
