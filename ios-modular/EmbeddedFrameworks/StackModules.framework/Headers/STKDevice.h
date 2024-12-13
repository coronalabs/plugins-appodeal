//
//  STKDevice.h
//  StackFounation
//
//  Created by Ilia Lozhkin on 6/26/19.
//  Copyright © 2019 Stack. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <StackModules/STKFoundationDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// Collect device information
@interface STKDevice : NSObject
/// Device model enum
@property (class, nonatomic, readonly) STKDeviceType type;
/// Check that current os version is lower that or equal to passed
@property (class, nonatomic, readonly) BOOL(^availableIOS)(NSUInteger);
/// Detects that device is connected to debugger in runtime
@property (class, nonatomic, readonly, getter=isDebug) BOOL debug;
/// Identifies notch
@property (class, nonatomic, readonly, getter=isXFamily) BOOL xFamily;
/// Check that device is phone
@property (class, nonatomic, readonly, getter=isIPhone) BOOL iPhone;
/// Check that device is phone
@property (class, nonatomic, readonly) BOOL isIphone DEPRECATED_MSG_ATTRIBUTE("Use isIPhone instead");
/// Detects jail break
@property (class, nonatomic, readonly, getter=isJailbroken) BOOL jailbroken;
/// Validate that app contains App Transport security settings that allows
/// connections over HTTP (insecure traffic)
@property (class, nonatomic, readonly, getter=isHTTPSupport) BOOL HTTPSupport;
/// Detects that battery saver mode is enabled or not
@property (class, nonatomic, readonly, getter=isLowPowerMode) BOOL lowPowerMode;
/// Detects that vired headset is connected
@property (class, nonatomic, readonly, getter=isHeadsetConnected) BOOL headsetConnected;
/// Name of os, probaly ios
@property (class, nonatomic, readonly) NSString *os;
/// Version of iOS
@property (class, nonatomic, readonly) NSString *osv;
/// Version of iOS
@property (class, nonatomic, readonly) NSString *osV DEPRECATED_MSG_ATTRIBUTE("Use osv instead");
/// Version of iOS
@property (class, nonatomic, readonly) NSString *hardwarev;
/// Version of iOS
@property (class, nonatomic, readonly) NSString *hardwareV DEPRECATED_MSG_ATTRIBUTE("Use hardwarev instead");
/// apple
@property (class, nonatomic, readonly) NSString *maker;
/// Machine name of device
@property (class, nonatomic, readonly) NSString *name;
/// User given name of device
@property (class, nonatomic, readonly) NSString *userName;
/// Screen brightness 0...1
@property (class, nonatomic, readonly) float brightness;
/// Device processors count
@property (class, nonatomic, readonly) NSNumber *processorsCount;
/// First preffered langauge
@property (class, nonatomic, readonly) NSString *language;
/// Currnet locale langauge code, available since iOS 10
@property (class, nonatomic, readonly) NSString *languageCode;
/// Currnet locale country code, available since iOS 10
@property (class, nonatomic, readonly) NSString *regionCode;
/// User agent
@property (class, nonatomic, readonly) NSString *userAgent;
/// Local timezone name
@property (class, nonatomic, readonly) NSString *timezone;
/// Boot date with secodns accuracy
@property (class, nonatomic, readonly) NSDate *bootdate;
/// Used cpu
@property (class, nonatomic, readonly) double cpuUsage;
/// Total RAM in bytes
@property (class, nonatomic, readonly) unsigned long long totalRAM;
/// Free RAM in bytes
@property (class, nonatomic, readonly) unsigned long long freeRAM;
/// Current RAM of app process
@property (class, nonatomic, readonly) unsigned long long currentRAM;
/// Audio output name
@property (class, nonatomic, readonly) NSString *audioOutput;
/// Audio output input
@property (class, nonatomic, readonly) NSString *audioInput;
/// Output volume 0...1
@property (class, nonatomic, readonly) float outputVolume;
/// State of battery: charging, full, unplugged, unknown
@property (class, nonatomic, readonly) NSString *batteryState;
/// Battery level 0...1
@property (class, nonatomic, readonly) float batteryLevel;
/// Total hard drive space in bytes
@property (class, nonatomic, readonly) NSNumber *totalDiskSpaceBytes;
/// Free hard drive space in bytes
@property (class, nonatomic, readonly) NSNumber *freeDiskSpaceBytes;
/// Used hard drive space in bytes
@property (class, nonatomic, readonly) NSNumber *usedDiskSpaceBytes;
/// Detects sound ringer state
/// @param completion closure that contains ringer state: mute/unmute
+ (void)checkMuted:(void(^)(BOOL))completion;
@end

NS_ASSUME_NONNULL_END
