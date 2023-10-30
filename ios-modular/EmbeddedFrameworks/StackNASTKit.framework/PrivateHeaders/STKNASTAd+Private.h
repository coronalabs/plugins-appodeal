//
//  STKNASTAd+Private.h
//  StackNASTKit
//
//  Created by Lozhkin Ilya on 5/31/18.
//  Copyright © 2018 Appodeal. All rights reserved.
//

#import <StackNASTKit/STKNASTAd.h>
#import <StackNASTKit/STKNASTManager.h>

@interface STKNASTAd ()

+ (void)parseJSON:(NSDictionary *)JSON
       comparator:(NSDictionary *)comparator
       completion:(STKNASTCompletionBlock)completion;

@end
