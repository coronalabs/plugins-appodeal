//
//  StackCrashReporter.h
//  StackCrashReporter
//
//  Created by Stas Kochkin on 23.11.2020.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(ReportFormat)
typedef NS_ENUM(NSInteger, SCRReportFormat) {
    SCRReportFormatBase = 0,
    SCRReportFormatExtended
};

NS_SWIFT_NAME(StackCrashReporter)
@interface StackCrashReporter : NSObject

@property (nonatomic, assign) SCRReportFormat format;
@property (nonatomic, copy) NSURL *baseURL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

+ (instancetype)sharedInstance;

- (void)install;
- (void)setCustomData:(NSDictionary <NSString *, id> *)customData;
- (void)sendReports:(void (^)(BOOL, NSError * _Nullable))completion;
- (void)addBreadcrumbMessage:(NSString *)breadcrumbMessage;
- (void)clearReportStorage;

@end

NS_ASSUME_NONNULL_END

