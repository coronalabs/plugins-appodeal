//
//  STKFoundationDefines.h
//  StackFoundation
//
//  Created by Stas Kochkin on 23.07.2020.
//  Copyright © 2020 Stack. All rights reserved.
//
#import <Foundation/Foundation.h>


typedef NS_ENUM(NSUInteger, STKDeviceType) {
    STKDeviceTypeUnknown,
    STKDeviceTypeIphone,
    STKDeviceTypeIphone3G,
    STKDeviceTypeIphone3GS,
    STKDeviceTypeIphone4,
    STKDeviceTypeIphone4s,
    STKDeviceTypeIphone5,
    STKDeviceTypeIphone5c,
    STKDeviceTypeIphone5s,
    STKDeviceTypeIphone6,
    STKDeviceTypeIphone6Plus,
    STKDeviceTypeIphone6s,
    STKDeviceTypeIphone6sPlus,
    STKDeviceTypeIphoneSE,
    STKDeviceTypeIphone7,
    STKDeviceTypeIphone7Plus,
    STKDeviceTypeIphone8,
    STKDeviceTypeIphone8Plus,
    STKDeviceTypeIphoneSEGen2,
    STKDeviceTypeIphoneX,
    STKDeviceTypeIphoneXR,
    STKDeviceTypeIphoneXS,
    STKDeviceTypeIphoneXSMax,
    STKDeviceTypeIphone11,
    STKDeviceTypeIphone11Pro,
    STKDeviceTypeIphone11ProMax,
    STKDeviceTypeIphoneSE2,
    STKDeviceTypeIphone12Mini,
    STKDeviceTypeIphone12,
    STKDeviceTypeIphone12Pro,
    STKDeviceTypeIphone12ProMax,
    
    STKDeviceTypeIpad,
    STKDeviceTypeIpad2,
    STKDeviceTypeIpadGen3,
    STKDeviceTypeIpadGen4,
    STKDeviceTypeIpadAir,
    STKDeviceTypeIpadAir2,
    STKDeviceTypeIpadPro129,
    STKDeviceTypeIpadPro97,
    STKDeviceTypeIpad5Gen,
    STKDeviceTypeIpadPro129Gen2,
    STKDeviceTypeIpadPro105,
    STKDeviceTypeIpadGen6,
    STKDeviceTypeIpadPro11,
    STKDeviceTypeIpadPro129Gen3,
    STKDeviceTypeIpadAirGen3,
    
    STKDeviceTypeIpadMini,
    STKDeviceTypeIpadMini2,
    STKDeviceTypeIpadMini3,
    STKDeviceTypeIpadMini4,
    STKDeviceTypeIpadMiniGen5,

    STKDeviceTypeIpadGen8,
    STKDeviceTypeIpadAirGen4,
    
    STKDeviceTypeIPod1,
    STKDeviceTypeIPod2,
    STKDeviceTypeIPod3,
    STKDeviceTypeIPod4,
    STKDeviceTypeIPod5,
    STKDeviceTypeIPod6,
    STKDeviceTypeIPod7,
};

NSDictionary <NSString *, NSNumber *> *STKDeviceTypeMap(void);
