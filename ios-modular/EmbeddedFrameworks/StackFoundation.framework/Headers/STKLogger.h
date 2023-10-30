//
//  STKLogger.h
//  StackFoundation
//
//  Created by Ilia Lozhkin on 7/4/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#ifndef STKLogger_h
#define STKLogger_h

#import <StackFoundation/STKLoggerDefines.h>

FOUNDATION_EXPORT void STKLogSetLevel(STKLogLevel level);

FOUNDATION_EXPORT void STKLogRegisterRecorder(id<STKLogRecorder> recorder, id<STKLogFormatter> formatter);

#endif /* STKLogger_h */
