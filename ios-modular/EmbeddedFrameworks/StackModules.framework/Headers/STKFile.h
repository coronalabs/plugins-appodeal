//
//  STKFile.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/2/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class STKFile;

typedef void(^STKSucceededFileBlock)(STKFile *);
typedef void(^STKMultipleSucceededFileBlock)(NSArray <STKFile *>*);
typedef void(^STKFailureFileBlock)(NSError *);

typedef enum : NSUInteger {
    STKFileTypeUndefined = 0,
    STKFileTypeJPG,
    STKFileTypePNG,
    STKFileTypeMP4,
    STKFileTypeMOV,
    STKFileTypeAVI,
    STKFileTypeSVG,
} STKFileType;

@interface STKFile : NSObject <NSCoding>

@property (nonatomic, readonly) NSURL *publicUrl;
@property (nonatomic, readonly) NSURL *localUrl;

@property (nonatomic, readonly) NSString *mimeType;
@property (nonatomic, readonly) NSString *prettyType;
@property (nonatomic, readonly) STKFileType type;

@property (nonatomic, readonly) CGSize size;
@property (nonatomic, readonly) NSData *data;

@property (class, nonatomic, readonly) STKFile *(^file)(NSURL *publicUrl, NSURL *localUrl, NSString *mimeType);

@end

NS_ASSUME_NONNULL_END
