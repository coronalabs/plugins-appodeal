//
//  STKLoggerDefines.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NSString * STKLogCategory;

FOUNDATION_EXPORT STKLogCategory STKLogCategoryDefault;
FOUNDATION_EXPORT STKLogCategory STKLogCategoryFromName(NSString *name);

typedef NS_OPTIONS(NSUInteger, STKLogFlag) {
    STKLogFlagError   = 1 << 0,
    STKLogFlagWarning = 1 << 1,
    STKLogFlagInfo    = 1 << 2,
    STKLogFlagDebug   = 1 << 3,
    STKLogFlagVerbose = 1 << 4
};

typedef NS_ENUM(NSUInteger, STKLogLevel) {
    STKLogLevelOff     = 0,
    STKLogLevelError   = STKLogFlagError,
    STKLogLevelWarning = STKLogLevelError   | STKLogFlagWarning,
    STKLogLevelInfo    = STKLogLevelWarning | STKLogFlagInfo,
    STKLogLevelDebug   = STKLogLevelInfo    | STKLogFlagDebug,
    STKLogLevelVerbose = STKLogLevelDebug   | STKLogFlagVerbose
};

OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogError(STKLogCategory,     NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogWarning(STKLogCategory,   NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogInfo(STKLogCategory,      NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogDebug(STKLogCategory,     NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogVerbose(STKLogCategory,   NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;

OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogError(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogWarning(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogInfo(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogDebug(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;
OS_OVERLOADABLE FOUNDATION_EXPORT void _STKLogVerbose(NSString *format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;

FOUNDATION_EXPORT void _STKLogSendMessage(NSString *message, STKLogCategory category, STKLogLevel logLevel);

#define STKLogCategoryError(_cat, ...)          _STKLogError(_cat,     __VA_ARGS__)
#define STKLogCategoryWarning(_cat, ...)        _STKLogWarning(_cat,   __VA_ARGS__)
#define STKLogCategoryInfo(_cat, ...)           _STKLogInfo(_cat,      __VA_ARGS__)
#define STKLogCategoryDebug(_cat, ...)          _STKLogDebug(_cat,     __VA_ARGS__)
#define STKLogCategoryVerbose(_cat, ...)        _STKLogVerbose(_cat,   __VA_ARGS__)

#define STKLogError(...)                        _STKLogError(STKLogCategoryDefault,     __VA_ARGS__)
#define STKLogWarning(...)                      _STKLogWarning(STKLogCategoryDefault,   __VA_ARGS__)
#define STKLogInfo(...)                         _STKLogInfo(STKLogCategoryDefault,      __VA_ARGS__)
#define STKLogDebug(...)                        _STKLogDebug(STKLogCategoryDefault,     __VA_ARGS__)
#define STKLogVerbose(...)                      _STKLogVerbose(STKLogCategoryDefault,   __VA_ARGS__)

@protocol STKLogFormatter <NSObject>

@optional

- (NSString *)formatForLogMessage:(NSString *)logMessage withLogLevel:(STKLogLevel)logLevel;

- (NSString *)formatForLogMessage:(NSString *)logMessage fromCategory:(STKLogCategory)category withLogLevel:(STKLogLevel)logLevel;

@end

@protocol STKLogRecorder <NSObject>

@property (nonatomic, strong) STKLogCategory category;

- (void)logMessage:(NSString *)logMessage
             level:(STKLogLevel)level;

@optional
@property (nonatomic, readonly) STKLogLevel level;

@end
