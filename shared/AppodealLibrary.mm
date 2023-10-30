//----------------------------------------------------------------------------
// AppodealLibrary.mm
//
// Copyright (c) 2016 Corona Labs. All rights reserved.
//----------------------------------------------------------------------------

// Apple
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>

// Corona
#import "CoronaRuntime.h"
#import "CoronaAssert.h"
#import "CoronaEvent.h"
#import "CoronaLua.h"
#import "CoronaLuaIOS.h"
#import "CoronaLibrary.h"
#import "CoronaVersion.h"
#import <AppTrackingTransparency/AppTrackingTransparency.h>

// Plugin specific imports
#import "AppodealLibrary.h"
#import <Appodeal/Appodeal.h>

// some macros to make life easier, and code more readable
#define UTF8StringWithFormat(format, ...) [[NSString stringWithFormat:format, ##__VA_ARGS__] UTF8String]
#define MsgFormat(format, ...) [NSString stringWithFormat:format, ##__VA_ARGS__]
#define UTF8IsEqual(utf8str1, utf8str2) (strcmp(utf8str1, utf8str2) == 0)

#define NO_VALUE INT_MAX
#define NO_ADTYPE 0

// ----------------------------------------------------------------------------
// Plugin Constants
// ----------------------------------------------------------------------------

#define PLUGIN_NAME        "plugin.appodeal"
#define PLUGIN_VERSION     "1.8.0"
#define PLUGIN_SDK_VERSION  [Appodeal getVersion]



static const char EVENT_NAME[]    = "adsRequest";
static const char PROVIDER_NAME[] = "appodeal";

// ad types
static const char TYPE_BANNER[]        = "banner";
static const char TYPE_INTERSTITIAL[]  = "interstitial";
static const char TYPE_REWARDEDVIDEO[] = "rewardedVideo";

// valid ad types
static const NSArray *validAdTypes = @[
	@(TYPE_BANNER),
	@(TYPE_INTERSTITIAL),
	@(TYPE_REWARDEDVIDEO)
];

// gender types
static const char GENDER_FEMALE[] = "female";
static const char GENDER_MALE[]   = "male";
static const char GENDER_OTHER[]  = "other";

// banner alignment
static const char BANNER_ALIGN_TOP[]    = "top";
static const char BANNER_ALIGN_BOTTOM[] = "bottom";

// event phases
static NSString * const PHASE_INIT           = @"init";
static NSString * const PHASE_DISPLAYED      = @"displayed";
static NSString * const PHASE_LOADED         = @"loaded";
static NSString * const PHASE_FAILED         = @"failed";
static NSString * const PHASE_CLOSED         = @"closed";
static NSString * const PHASE_CLICKED        = @"clicked";
static NSString * const PHASE_PLAYBACK_BEGAN = @"playbackBegan";
static NSString * const PHASE_PLAYBACK_ENDED = @"playbackEnded";
static NSString * const PHASE_DATA_RECEIVED  = @"dataReceived";
static NSString * const PHASE_HIDDEN         = @"hidden";

// response codes
static NSString * const RESPONSE_LOADFAILED  = @"failed to load";
static NSString * const RESPONSE_PRESENTFAILED  = @"failed to present";

// missing Corona Event Keys
static NSString * const CORONA_EVENT_DATA_KEY = @"data";

// data keys
static NSString * const REWARD_AMOUNT_KEY = @"amount";
static NSString * const REWARD_NAME_KEY   = @"name";

// message constants
static NSString * const ERROR_MSG   = @"ERROR: ";
static NSString * const WARNING_MSG = @"WARNING: ";

// saved objects (apiKey, ad state, etc)
static NSMutableDictionary *appodealObjects;

// object dictionary keys
static NSString * const SUPPORTED_ADTYPES_KEY = @"supportedAdTypes";
static NSString * const AUTOCACHE_KEY         = @"disableAutoCacheForAdTypes";

// ----------------------------------------------------------------------------
// plugin class and delegate definitions
// ----------------------------------------------------------------------------

@interface AppodealPluginDelegate : UIViewController <AppodealBannerDelegate, AppodealInterstitialDelegate, AppodealRewardedVideoDelegate>

@property (nonatomic, assign) CoronaLuaRef coronaListener;
@property (nonatomic, weak) id<CoronaRuntime> coronaRuntime;
@property (nonatomic, assign) bool sdkInitialized;

- (void)dispatchLuaEvent:(NSDictionary *)dict;

@end

//----------------------------------------------------------------------------

class AppodealLibrary
{
public:
	typedef AppodealLibrary Self;
	
public:
	static const char kName[];
	
public:
	static int Open(lua_State *L);
	static int Finalizer(lua_State *L);
	static Self *ToLibrary(lua_State *L);
	
protected:
	AppodealLibrary();
	bool Initialize(void *platformContext);
	
public:
	static int init(lua_State *L);
	static int show(lua_State *L);
	static int hide(lua_State *L);
	static int load(lua_State *L);
	static int isLoaded(lua_State *L);
	static int setUserDetails(lua_State *L);
	static int getRewardParameters(lua_State *L);
	static int getVersion(lua_State *L);
	static int canShow(lua_State *L);
	static int setSegmentFilter(lua_State *L);
	static int trackInAppPurchase(lua_State *L);
	
private: // internal helper functions
	static void logMsg(lua_State *L, NSString *msgType,  NSString *errorMsg);
	static bool isSDKInitialized(lua_State *L);
	static void setRules(NSMutableDictionary *customRules);
	
private:
	NSString *functionSignature;                                  // used in logMsg to identify function
	UIViewController *coronaViewController;
};

//----------------------------------------------------------------------------

const char AppodealLibrary::kName[] = PLUGIN_NAME;
static AppodealPluginDelegate *appodealPluginDelegate = nil;

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

// log message to console
void
AppodealLibrary::logMsg(lua_State *L, NSString* msgType, NSString* errorMsg)
{
	Self *context = ToLibrary(L);
	
	if (context) {
		Self& library = *context;
		
		NSString *functionID = [library.functionSignature copy];
		if (functionID.length > 0) {
			functionID = [functionID stringByAppendingString:@", "];
		}
		
		CoronaLuaLogPrefix(L, [msgType UTF8String], UTF8StringWithFormat(@"%@%@", functionID, errorMsg));
	}
}

// check if SDK calls can be made
bool
AppodealLibrary::isSDKInitialized(lua_State *L)
{
	if (appodealPluginDelegate.coronaListener == NULL) {
		logMsg(L, ERROR_MSG, @"appodeal.init() must be called before calling other API methods");
		return false;
	}
	
	if (! appodealPluginDelegate.sdkInitialized) {
		logMsg(L, ERROR_MSG, @"appodeal.init() was called with incorrect parameters");
		return false;
	}
	
	return true;
}

// set custom rules
void
AppodealLibrary::setRules(NSMutableDictionary *customRules)
{
	// we need to convert Float64 to Float32 for the Appodeal SDK to work properly
	NSMutableDictionary *float32Dict = [NSMutableDictionary new];
	
	for (NSString *key in customRules) {
		if ([customRules[key] isKindOfClass:[NSNumber class]]) {
			NSNumber *oldNumber = customRules[key];
			CFNumberType oldNumberType = CFNumberGetType((CFNumberRef)oldNumber);
			
			// convert Float64 to Float32
			if (oldNumberType == kCFNumberFloat64Type) {
				float newFloat = [oldNumber floatValue];
				CFNumberRef newNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberFloat32Type, &newFloat);
				float32Dict[key] = (NSNumber *)CFBridgingRelease(newNumberRef);
			}
		}
	}
	
	// update the custom rules dictionary with Float32 values
	for (NSString *key32 in float32Dict) {
		customRules[key32] = float32Dict[key32];
	}
	
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
	if([Appodeal respondsToSelector:@selector(setSegmentFilter:)]) {
		[Appodeal performSelector:@selector(setSegmentFilter:) withObject:customRules];
	}
	else if([Appodeal respondsToSelector:@selector(setCustomRule:)]) {
		[Appodeal performSelector:@selector(setCustomRule:) withObject:customRules];
	}
#pragma clang diagnostic pop
}

// ----------------------------------------------------------------------------
// plugin implementation
// ----------------------------------------------------------------------------

AppodealLibrary::AppodealLibrary()
:	coronaViewController(nil)
{
}

bool
AppodealLibrary::Initialize(void *platformContext)
{
	bool shouldInit = (coronaViewController == nil);
	
	if (shouldInit) {
		id<CoronaRuntime> runtime = (__bridge id<CoronaRuntime>)platformContext;
		coronaViewController = runtime.appViewController;
		
		// Initialise the delegate
		appodealPluginDelegate = [AppodealPluginDelegate new];
		appodealPluginDelegate.coronaRuntime = runtime;
		
		// initialize ad object dictionary
		appodealObjects = [NSMutableDictionary new];
	}
	
	return shouldInit;
}

// Open the library
int
AppodealLibrary::Open(lua_State *L)
{
	// Register __gc callback
	const char kMetatableName[] = __FILE__; // Globally unique string to prevent collision
	CoronaLuaInitializeGCMetatable(L, kMetatableName, Finalizer);
	
	void *platformContext = CoronaLuaGetContext(L);
	
	// Set library as upvalue for each library function
	Self *library = new Self;
	
	if (library->Initialize(platformContext))
	{
		// Functions in library
		static const luaL_Reg kFunctions[] =
		{
			{"init", init},
			{"show", show},
			{"hide", hide},
			{"load", load},
			{"isLoaded", isLoaded},
			{"setUserDetails", setUserDetails},
			{"getRewardParameters", getRewardParameters},
			{"getVersion", getVersion},
			{"canShow", canShow},
			{"setSegmentFilter", setSegmentFilter},
			{"trackInAppPurchase", trackInAppPurchase},
			{NULL, NULL}
		};
		
		// Register functions as closures, giving each access to the
		// 'library' instance via ToLibrary()
		{
			CoronaLuaPushUserdata(L, library, kMetatableName);
			luaL_openlib(L, kName, kFunctions, 1); // leave "library" on top of stack
		}
	}
	
	return 1;
}

int
AppodealLibrary::Finalizer(lua_State *L)
{
	Self *library = (Self *)CoronaLuaToUserdata(L, 1);
	
	CoronaLuaDeleteRef(L, appodealPluginDelegate.coronaListener);
	appodealPluginDelegate.coronaListener = NULL;
	appodealPluginDelegate = nil;
	
	delete library;
	
	return 0;
}

AppodealLibrary *
AppodealLibrary::ToLibrary(lua_State *L)
{
	// library is pushed as part of the closure
	Self *library = (Self *)CoronaLuaToUserdata(L, lua_upvalueindex(1));
	return library;
}

static void InitAppodeal(AppodealAdType adTypes, const char *appKey, bool testMode) {
        
        // set delegates / log level
        [Appodeal setBannerDelegate:appodealPluginDelegate];
        [Appodeal setInterstitialDelegate:appodealPluginDelegate];
        [Appodeal setRewardedVideoDelegate:appodealPluginDelegate];

        [Appodeal setAutocache:YES types:adTypes]; // At moment appodeal requires this
        
        if (testMode) {
            [Appodeal setTestingEnabled:YES];
            [APDSdk setLogLevel:APDLogLevelVerbose];
        }
        
        [Appodeal setFramework:APDFrameworkCorona version:[NSString stringWithUTF8String:CoronaVersionBuildString()]];
        // log the plugin version to device console
        NSLog(@"Corona/Solar2D Appodeal %s: %s (SDK: %@)", PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_SDK_VERSION);
        
        appodealPluginDelegate.sdkInitialized = true;
        
        [Appodeal initializeWithApiKey:@(appKey) types:adTypes];
        // send Corona Lua event
        NSDictionary *coronaEvent = @{
            @(CoronaEventPhaseKey()) : PHASE_INIT
        };
        [appodealPluginDelegate dispatchLuaEvent:coronaEvent];
}

// [Lua] appodeal.init(listener, options)
int
AppodealLibrary::init(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.init(listener, options)";
	
	// prevent init from being called twice
	if (appodealPluginDelegate.coronaListener != NULL) {
		logMsg(L, WARNING_MSG, @"init() should only be called once");
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 2) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 2 arguments, got %d", nargs));
		return 0;
	}
	
	// params
	const char *appKey = NULL;
	bool testMode = false;
	bool smartBanners = true;
	bool bannerAnimation = false;
	bool childDirectedTreatment = false;
	bool childDirectedTreatmentIsSet = false;
	bool locationTracking = false;
	NSMutableArray *disabledAutoCacheAdTypes = [NSMutableArray new];
	NSMutableArray *supportedAdTypes = [NSMutableArray new];
	NSMutableArray *disabledAdNetworks = [NSMutableArray new];
	NSMutableDictionary *customRules = nil;
	bool hasUserConsent = false;
	
	// Get listener key (required)
	if (CoronaLuaIsListener(L, 1, PROVIDER_NAME)) {
		appodealPluginDelegate.coronaListener = CoronaLuaNewRef(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"listener expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	// check for options table (required)
	if (lua_type(L, 2) == LUA_TTABLE) {
		// traverse and verify all options
		for (lua_pushnil(L); lua_next(L, 2) != 0; lua_pop(L, 1)) {
			const char *key = lua_tostring(L, -2);
			
			if (UTF8IsEqual(key, "appKey")) {
				if (lua_type(L, -1) == LUA_TSTRING) {
					appKey = lua_tostring(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.appKey (string) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "testMode")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					testMode = lua_toboolean(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.testMode (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "disableAutoCacheForAdTypes")) {
				if (lua_type(L, -1) == LUA_TTABLE) {
					// build disabled autocache ad types
					int ntypes = (int)lua_objlen(L, -1);
					
					if (ntypes > 0) {
						for (int i=1; i<=ntypes; i++) {
							//push array value onto stack
							lua_rawgeti(L, -1, i);
							
							// add ad type to array
							if (lua_type(L, -1) == LUA_TSTRING) {
								[disabledAutoCacheAdTypes addObject:@(lua_tostring(L, -1))];
							}
							else {
								logMsg(L, ERROR_MSG, MsgFormat(@"options.disableAutoCacheForAdTypes[%d] (string) expected, got: %s", i, luaL_typename(L, -1)));
								return 0;
							}
							lua_pop(L, 1);
						}
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.disableAutoCacheForAdTypes table cannot be empty"));
						return 0;
					}
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.disableAutoCacheForAdTypes (table) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "smartBanners")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					smartBanners = lua_toboolean(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.smartBanners (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "bannerAnimation")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					bannerAnimation = lua_toboolean(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.bannerAnimation (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "childDirectedTreatment")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					childDirectedTreatmentIsSet = true;
					childDirectedTreatment = lua_toboolean(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.childDirectedTreatment (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "locationTracking")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					locationTracking = lua_toboolean(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.locationTracking (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "customRules")) {
				if (lua_type(L, -1) == LUA_TTABLE) {
					// we need gettop() here since -1 will return nil
					// we also need to make it mutable (see below for float64 to float32 conversion)
					customRules = [CoronaLuaCreateDictionary(L, lua_gettop(L)) mutableCopy];
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.customRules (table) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "supportedAdTypes")) {
				if (lua_type(L, -1) == LUA_TTABLE) {
					// build supported ad types
					int ntypes = (int)lua_objlen(L, -1);
					
					if (ntypes > 0) {
						for (int i=1; i<=ntypes; i++) {
							//push array value onto stack
							lua_rawgeti(L, -1, i);
							
							// add ad type to array
							if (lua_type(L, -1) == LUA_TSTRING) {
								[supportedAdTypes addObject:@(lua_tostring(L, -1))];
							}
							else {
								logMsg(L, ERROR_MSG, MsgFormat(@"options.supportedAdTypes[%d] (string) expected, got: %s", i, luaL_typename(L, -1)));
								return 0;
							}
							lua_pop(L, 1);
						}
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.supportedAdTypes table cannot be empty"));
						return 0;
					}
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.supportedAdType (table) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "disableNetworks")) {
				if (lua_type(L, -1) == LUA_TTABLE) {
					// build supported ad types
					int ntypes = (int)lua_objlen(L, -1);
					
					if (ntypes > 0) {
						for (int i=1; i<=ntypes; i++) {
							//push array value onto stack
							lua_rawgeti(L, -1, i);
							
							// add ad type to array
							if (lua_type(L, -1) == LUA_TSTRING) {
								[disabledAdNetworks addObject:@(lua_tostring(L, -1))];
							}
							else {
								logMsg(L, ERROR_MSG, MsgFormat(@"options.disableNetworks[%d] (string) expected, got: %s", i, luaL_typename(L, -1)));
								return 0;
							}
							lua_pop(L, 1);
						}
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.disableNetworks table cannot be empty"));
						return 0;
					}
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.disableNetworks (table) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "hasUserConsent")) {
				if (lua_type(L, -1) == LUA_TBOOLEAN) {
					hasUserConsent = lua_toboolean(L, -1);
                    if(hasUserConsent){
                        [Appodeal updateUserConsentGDPR:APDGDPRUserConsentPersonalized];
                        [Appodeal updateUserConsentCCPA:APDCCPAUserConsentOptIn];
                    }else{
                        [Appodeal updateUserConsentGDPR:APDGDPRUserConsentNonPersonalized];
                        [Appodeal updateUserConsentCCPA:APDCCPAUserConsentOptOut];
                    }
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.hasUserConsent (boolean) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (!UTF8IsEqual(key, "disableWriteExternalPermissionCheck")) {
				if (UTF8IsEqual(key, "autoCacheAds")) {
					logMsg(L, ERROR_MSG, MsgFormat(@"Parameter autoCacheAds was deprecated. Use disableAutoCacheForAdTypes instead"));
				} else {
					logMsg(L, ERROR_MSG, MsgFormat(@"Invalid option '%s'", key));
				}
				return 0;
				
			}
		}
	}
	// no options table
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"options table expected, got %s", luaL_typename(L, 2)));
		return 0;
	}
	
	// validate appKey
	if (appKey == NULL) {
		logMsg(L, ERROR_MSG, @"options.appKey missing");
		return 0;
	}
	
	// simple key/value validation for custom rules
	for (NSString *key in customRules) {
		if ([key isKindOfClass:[NSNumber class]]) {
			logMsg(L, ERROR_MSG, @"options.customRules should be a key/value table");
			return 0;
		}
	}
	
	// validate supported ad types
	AppodealAdType adTypes = NO_ADTYPE;
	
	for (NSString *adType in supportedAdTypes) {
		if (! [validAdTypes containsObject:adType]) {
			logMsg(L, ERROR_MSG, MsgFormat(@"Invalid supportedAdType '%@'", adType));
			return 0;
		}
		
		if ([adType isEqualToString:@(TYPE_BANNER)]) {
			adTypes |= AppodealAdTypeBanner;
		}
		else if ([adType isEqualToString:@(TYPE_INTERSTITIAL)]) {
			adTypes |= AppodealAdTypeInterstitial;
		}
		else if ([adType isEqualToString:@(TYPE_REWARDEDVIDEO)]) {
			adTypes |= AppodealAdTypeRewardedVideo;
		}
	}
	
	// default to all ad types if none given
	if (adTypes == NO_ADTYPE) {
		adTypes = AppodealAdTypeRewardedVideo | AppodealAdTypeBanner | AppodealAdTypeInterstitial;;
		[supportedAdTypes addObject:@(TYPE_REWARDEDVIDEO)];
		[supportedAdTypes addObject:@(TYPE_BANNER)];
		[supportedAdTypes addObject:@(TYPE_INTERSTITIAL)];
	}
	
	// save data for future use
	appodealObjects[SUPPORTED_ADTYPES_KEY] = supportedAdTypes;
	appodealObjects[AUTOCACHE_KEY] = disabledAutoCacheAdTypes;
	
	// configure before SDK initialization
	[Appodeal setBannerAnimationEnabled:bannerAnimation];
	[Appodeal setSmartBannersEnabled:smartBanners];
	[Appodeal setFramework:APDFrameworkCorona version:nil];
	if(childDirectedTreatmentIsSet) {
		[Appodeal setChildDirectedTreatment:childDirectedTreatment];
	}
	
	if (customRules != nil) {
		setRules(customRules);
	}
	
	// disable ad networks (for internal user only)
	// developers should disable ad networks from their Appodeal dashboard
	if (disabledAdNetworks.count > 0) {
		// use Xcode's pragma push/pop to ignore deprecation notice for this code section only
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
		for (NSString *adNetwork in disabledAdNetworks) {
			NSLog(@"Disabling ad network %@ (WARNING: FOR INTERNAL CORONA USE ONLY)", adNetwork);
			[Appodeal disableNetworkForAdType:adTypes name:adNetwork];
		}
#pragma clang diagnostic pop
	}
	
	// Disable autocache for selected ad types
	if (disabledAutoCacheAdTypes.count > 0) {
		AppodealAdType adTypes = NO_ADTYPE;
		
		for (NSString *adType in disabledAutoCacheAdTypes) {
			if (! [validAdTypes containsObject:adType]) {
				logMsg(L, ERROR_MSG, MsgFormat(@"Invalid disabledAutoCacheAdType '%@'", adType));
				return 0;
			}
			
			if ([adType isEqualToString:@(TYPE_BANNER)]) {
				adTypes |= AppodealAdTypeBanner;
			}
			else if ([adType isEqualToString:@(TYPE_INTERSTITIAL)]) {
				adTypes |= AppodealAdTypeInterstitial;
			}
			else if ([adType isEqualToString:@(TYPE_REWARDEDVIDEO)]) {
				adTypes |= AppodealAdTypeRewardedVideo;
			}
		}
		
		[Appodeal setAutocache:false types:adTypes];
	}
	
	[Appodeal setTestingEnabled:testMode];
	[Appodeal setLocationTracking:locationTracking];
	
	// Initialise the SDK
	if([[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSUserTrackingUsageDescription"]) {
		if (@available(iOS 14, *)) {
			[ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
				InitAppodeal(adTypes, appKey, testMode);
			}];
		} else {
			InitAppodeal(adTypes, appKey, testMode);
		}
	} else {
		InitAppodeal(adTypes, appKey, testMode);
	}
	
	return 0;
}

// [Lua] appodeal.show(adUnitType, [options])
int
AppodealLibrary::show(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.show(adUnitType [, options])";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if ((nargs < 1) || (nargs > 2)) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 or 2 arguments, got %d", nargs));
		return 0;
	}
	
	const char *adUnitType = NULL;
	const char *placement = NULL;
	const char *yAlign = BANNER_ALIGN_BOTTOM;
	
	// Ensure the adUnitType is a string
	if (lua_type(L, 1) == LUA_TSTRING) {
		adUnitType = lua_tostring(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType (string) expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	if (! lua_isnoneornil(L, 2)) {
		// check for options table
		if (lua_type(L, 2) == LUA_TTABLE) {
			// traverse and verify all options
			for (lua_pushnil(L); lua_next(L, 2) != 0; lua_pop(L, 1)) {
				const char *key = lua_tostring(L, -2);
				
				if (UTF8IsEqual(key, "yAlign")) {
					if (lua_type(L, -1) == LUA_TSTRING) {
						yAlign = lua_tostring(L, -1);
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.yAlign (string) expected, got: %s", luaL_typename(L, -1)));
						return 0;
					}
				}
				else if (UTF8IsEqual(key, "placement")) {
					if (lua_type(L, -1) == LUA_TSTRING) {
						placement = lua_tostring(L, -1);
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.placement (string) expected, got: %s", luaL_typename(L, -1)));
						return 0;
					}
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"Invalid option '%s'", key));
					return 0;
				}
			}
		}
		// no options table
		else {
			logMsg(L, ERROR_MSG, MsgFormat(@"options table expected, got %s", luaL_typename(L, 2)));
			return 0;
		}
	}
	
	// validate ad unit type
	if (! [validAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Invalid adUnitType '%s'", adUnitType));
		return 0;
	}
	
	// make sure ad unit type was specified during init()
	NSMutableArray *supportedAdTypes = appodealObjects[SUPPORTED_ADTYPES_KEY];
	if (! [supportedAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. You didn't specify '%s' in supportedAdTypes during init()", adUnitType));
		return 0;
	}
	
	// validate yAlign
	if ((! UTF8IsEqual(yAlign, BANNER_ALIGN_BOTTOM)) && (! UTF8IsEqual(yAlign, BANNER_ALIGN_TOP))) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Invalid yAlign '%s'", yAlign));
		return 0;
	}
	
	// the type of ad to be displayed
	AppodealShowStyle showStyle = AppodealShowStyleInterstitial;
	
	if (UTF8IsEqual(adUnitType, TYPE_BANNER)) {
		showStyle = UTF8IsEqual(yAlign, BANNER_ALIGN_BOTTOM) ? AppodealShowStyleBannerBottom : AppodealShowStyleBannerTop;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_INTERSTITIAL)) {
		showStyle = AppodealShowStyleInterstitial;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_REWARDEDVIDEO)) {
		showStyle = AppodealShowStyleRewardedVideo;
	}
	
	// do we have a placement?
	if (placement == NULL) {
		[Appodeal showAd:showStyle rootViewController:library.coronaViewController];
	}
	else {
		[Appodeal showAd:showStyle forPlacement:@(placement) rootViewController:library.coronaViewController];
	}
	
	return 0;
}

// [Lua] appodeal.hide(adUnitType)
int
AppodealLibrary::hide(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.hide(adUnitType)";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 argument, got %d", nargs));
		return 0;
	}
	
	const char *adUnitType = NULL;
	
	// Ensure the adUnitType is a string
	if (lua_type(L, 1) == LUA_TSTRING) {
		adUnitType = lua_tostring(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType (string) expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	// validate ad unit type
	if (! UTF8IsEqual(adUnitType, TYPE_BANNER)) {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType='%s'. Only banners can be hidden", adUnitType));
		return 0;
	}
	
	// make sure ad unit type was specified during init()
	NSMutableArray *supportedAdTypes = appodealObjects[SUPPORTED_ADTYPES_KEY];
	if (! [supportedAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. You didn't specify '%s' in supportedAdTypes during init()", adUnitType));
		return 0;
	}
	
	// only banners can be hidden
	[Appodeal hideBanner];
	
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_HIDDEN,
		@(CoronaEventTypeKey()): @(TYPE_BANNER)
	};
	[appodealPluginDelegate dispatchLuaEvent:coronaEvent];
	
	return 0;
}

// [Lua] appodeal.getRewardParameters( [placementId] )
int
AppodealLibrary::getRewardParameters(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.getRewardParameters( [placementId] )";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs > 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 0 or 1 argument, got %d", nargs));
		return 0;
	}
	
	const char *placementId = NULL;
	
	if (! lua_isnoneornil(L, 1)) {
		if (lua_type(L, 1) == LUA_TSTRING) {
			placementId = lua_tostring(L, 1);
		}
		else {
			logMsg(L, ERROR_MSG, MsgFormat(@"placementId (string) expected, got: %s", luaL_typename(L, 1)));
			return 0;
		}
	}
	
	id<APDReward> rewardInfo;
	
	if (placementId != NULL) {
		rewardInfo = [Appodeal rewardForPlacement:@(placementId)];
	}
	
	// get default placement if placement not found (to mimic Android SDK behavior)
	if (rewardInfo == nil) {
		logMsg(L, ERROR_MSG, MsgFormat(@"placementId '%s' not found", placementId));
		return 0;
	}
	
	// Create the reward event data
	NSDictionary *eventData = @{
		REWARD_AMOUNT_KEY: @(rewardInfo.amount),
		REWARD_NAME_KEY: rewardInfo.currencyName
	};
	
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_DATA_RECEIVED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		CORONA_EVENT_DATA_KEY: eventData
	};
	[appodealPluginDelegate dispatchLuaEvent:coronaEvent];
	
	return 0;
}

// [Lua] appodeal.getVersion()
int
AppodealLibrary::getVersion(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.getVersion()";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	logMsg(L, @"Data received:", MsgFormat(@"%s: %s (SDK: %@)", PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_SDK_VERSION));
	
	// Create the reward event data
	NSDictionary *eventData = @{
		@"pluginVersion": @PLUGIN_VERSION,
		@"sdkVersion": PLUGIN_SDK_VERSION
	};
	
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_INIT,
		@(CoronaEventDataKey()): eventData,
	};
	[appodealPluginDelegate dispatchLuaEvent:coronaEvent];
	
	return 0;
}

// [Lua] appodeal.load(adUnitType [, options ])
int
AppodealLibrary::load(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.load(adUnitType [, options ])";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if ((nargs < 1) || (nargs > 2)) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 or 2 arguments, got %d", nargs));
		return 0;
	}
	
	const char *adUnitType = NULL;
	const char *placement = NULL;
	
	// Ensure the adUnitType is a string
	if (lua_type(L, 1) == LUA_TSTRING) {
		adUnitType = lua_tostring(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType (string) expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	if (! lua_isnoneornil(L, 2)) {
		// check for options table
		if (lua_type(L, 2) == LUA_TTABLE) {
			// traverse and verify all options
			for (lua_pushnil(L); lua_next(L, 2) != 0; lua_pop(L, 1)) {
				const char *key = lua_tostring(L, -2);
				
				if (UTF8IsEqual(key, "placement")) {
					if (lua_type(L, -1) == LUA_TSTRING) {
						placement = lua_tostring(L, -1);
					}
					else {
						logMsg(L, ERROR_MSG, MsgFormat(@"options.placement (string) expected, got: %s", luaL_typename(L, -1)));
						return 0;
					}
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"Invalid option '%s'", key));
					return 0;
				}
			}
		}
		// no options table
		else {
			logMsg(L, ERROR_MSG, MsgFormat(@"options table expected, got %s", luaL_typename(L, 2)));
			return 0;
		}
	}
	
	// make sure disabled autocache ad unit type was specified during init()
	NSMutableArray *disabledAutoCacheAdTypes = appodealObjects[AUTOCACHE_KEY];
	if (! [disabledAutoCacheAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. Auto caching for '%s' must be turned off in disableAutoCacheForAdTypes during init() to load an ad manually", adUnitType));
		return 0;
	}
	
	// validate ad unit type
	if (! [validAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Invalid adUnitType '%s'", adUnitType));
		return 0;
	}
	
	// make sure ad unit type was specified during init()
	NSMutableArray *supportedAdTypes = appodealObjects[SUPPORTED_ADTYPES_KEY];
	if (! [supportedAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. You didn't specify '%s' in supportedAdTypes during init()", adUnitType));
		return 0;
	}
	
	// the type of ad to be displayed
	AppodealAdType adType = NO_VALUE;
	
	if (UTF8IsEqual(adUnitType, TYPE_BANNER)) {
		adType = AppodealAdTypeBanner;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_INTERSTITIAL)) {
		adType = AppodealAdTypeInterstitial;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_REWARDEDVIDEO)) {
		adType = AppodealAdTypeRewardedVideo;
	}
	
	if (placement == NULL) {
		[Appodeal cacheAd:adType];
	}
	else {
		//    [Appodeal cacheAd:adType forPlacement:@(placement)];
	}
	
	return 0;
}

// [Lua] appodeal.isLoaded(adUnitType)
int
AppodealLibrary::isLoaded(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.isLoaded(adUnitType)";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 argument, got %d", nargs));
		return 0;
	}
	
	const char *adUnitType = NULL;
	
	// Ensure the adUnitType is a string
	if (lua_type(L, 1) == LUA_TSTRING) {
		adUnitType = lua_tostring(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType (string) expected, got %s", luaL_typename(L, 1)));
		return 0;
	}
	
	// validate ad unit type
	if (! [validAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Invalid adUnitType '%s'", adUnitType));
		return 0;
	}
	
	// make sure ad unit type was specified during init()
	NSMutableArray *supportedAdTypes = appodealObjects[SUPPORTED_ADTYPES_KEY];
	if (! [supportedAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. You didn't specify '%s' in supportedAdTypes during init()", adUnitType));
		return 0;
	}
	
	// the type of ad to be displayed
	AppodealShowStyle showStyle = AppodealShowStyleInterstitial;
	
	if (UTF8IsEqual(adUnitType, TYPE_BANNER)) {
		showStyle = AppodealShowStyleBannerBottom;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_INTERSTITIAL)) {
		showStyle = AppodealShowStyleInterstitial;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_REWARDEDVIDEO)) {
		showStyle = AppodealShowStyleRewardedVideo;
	}
	
	bool isLoaded = [Appodeal isReadyForShowWithStyle:showStyle];
	lua_pushboolean(L, isLoaded);
	
	return 1;
}

// [Lua] appodeal.canShow(adUnitType, placement)
int
AppodealLibrary::canShow(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.canShow(adUnitType, placement)";
	
	if (! isSDKInitialized(L)) {
		return 0;
	}
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if ((nargs < 1) || (nargs > 2)) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 2 arguments, got %d", nargs));
		return 0;
	}
	
	const char *adUnitType = NULL;
	const char *placement = NULL;
	
	// Ensure the adUnitType is a string
	if (lua_type(L, 1) == LUA_TSTRING) {
		adUnitType = lua_tostring(L, 1);
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"adUnitType (string) expected, got %s", luaL_typename(L, 1)));
		return 0;
	}
	if (! lua_isnoneornil(L, 2)) {
		// Ensure the placement is a string
		if (lua_type(L, 2) == LUA_TSTRING) {
			placement = lua_tostring(L, 2);
		}
		else {
			logMsg(L, ERROR_MSG, MsgFormat(@"placement (string) expected, got %s", luaL_typename(L, 2)));
			return 0;
		}
	}
	// validate ad unit type
	if (! [validAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Invalid adUnitType '%s'", adUnitType));
		return 0;
	}
	
	// make sure ad unit type was specified during init()
	NSMutableArray *supportedAdTypes = appodealObjects[SUPPORTED_ADTYPES_KEY];
	if (! [supportedAdTypes containsObject:@(adUnitType)]) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Request ignored. You didn't specify '%s' in supportedAdTypes during init()", adUnitType));
		return 0;
	}
	
	// the type of ad to be displayed
	AppodealAdType adType = AppodealAdTypeInterstitial;
	
	if (UTF8IsEqual(adUnitType, TYPE_BANNER)) {
		adType =  AppodealAdTypeBanner;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_INTERSTITIAL)) {
		adType = AppodealAdTypeInterstitial;
	}
	else if (UTF8IsEqual(adUnitType, TYPE_REWARDEDVIDEO)) {
		adType = AppodealAdTypeRewardedVideo;
	}
	
	if (placement == NULL) {
		placement = "default";
	}
	
	bool canShow = [Appodeal canShow:adType forPlacement:@(placement)];
	lua_pushboolean(L, canShow);
	
	return 1;
}

// [Lua] appodeal.setSegmentFilter(options)
int
AppodealLibrary::setSegmentFilter(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.setSegmentFilter(options)";
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 argument, got %d", nargs));
		return 0;
	}
	
	// params
	NSMutableDictionary *customRules = nil;
	
	// check for options table
	if (lua_type(L, 1) == LUA_TTABLE) {
		// we need gettop() here since -1 will return nil
		// we also need to make it mutable (see below for float64 to float32 conversion)
		customRules = [CoronaLuaCreateDictionary(L, lua_gettop(L)) mutableCopy];
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"options.customRules (table) expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	if (customRules != nil) {
		// simple key/value validation for custom rules
		for (NSString *key in customRules) {
			if ([key isKindOfClass:[NSNumber class]]) {
				logMsg(L, ERROR_MSG, @"options.customRules should be a key/value table");
				return 0;
			}
		}
		
		setRules(customRules);
	}
	
	return 0;
}

// [Lua] appodeal.trackInAppPurchase(options)
int
AppodealLibrary::trackInAppPurchase(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.trackInAppPurchase(options)";
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 argument, got %d", nargs));
		return 0;
	}
	
	// params
	lua_Number amount = NO_VALUE;
	const char *currency = NULL;
	
	// check for options table
	if (lua_type(L, 1) == LUA_TTABLE) {
		for (lua_pushnil(L); lua_next(L, 1) != 0; lua_pop(L, 1)) {
			const char *key = lua_tostring(L, -2);
			
			if (UTF8IsEqual(key, "amount")) {
				if (lua_type(L, -1) == LUA_TNUMBER) {
					amount = lua_tonumber(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.amount (number) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "currency")) {
				if (lua_type(L, -1) == LUA_TSTRING) {
					currency = lua_tostring(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.currency (string) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else {
				logMsg(L, ERROR_MSG, MsgFormat(@"Invalid option '%s'", key));
				return 0;
			}
		}
	}
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"options (table) expected, got: %s", luaL_typename(L, 1)));
		return 0;
	}
	
	if (amount != NO_VALUE && currency != NULL) {
		[Appodeal trackInAppPurchase:@(amount) currency:@(currency)];
	}
	
	return 0;
}

// [Lua] appodeal.setUserDetails(options)
int
AppodealLibrary::setUserDetails(lua_State *L)
{
	Self *context = ToLibrary(L);
	
	if (! context) { // abort if no valid context
		return 0;
	}
	
	Self& library = *context;
	
	library.functionSignature = @"appodeal.setUserDetails(options)";
	
	// get number of arguments
	int nargs = lua_gettop(L);
	if (nargs != 1) {
		logMsg(L, ERROR_MSG, MsgFormat(@"Expected 1 argument, got %d", nargs));
		return 0;
	}
	
	// params
	lua_Number age = NO_VALUE;
	const char *gender = NULL;
	const char *userId = NULL;
	
	// check for options table
	if (lua_type(L, 1) == LUA_TTABLE) {
		// traverse and verify all options
		for (lua_pushnil(L); lua_next(L, 1) != 0; lua_pop(L, 1)) {
			const char *key = lua_tostring(L, -2);
			
			if (UTF8IsEqual(key, "age")) {
				if (lua_type(L, -1) == LUA_TNUMBER) {
					age = lua_tonumber(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.age (number) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "gender")) {
				if (lua_type(L, -1) == LUA_TSTRING) {
					gender = lua_tostring(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.gender (string) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else if (UTF8IsEqual(key, "userId")) {
				if (lua_type(L, -1) == LUA_TSTRING) {
					userId = lua_tostring(L, -1);
				}
				else {
					logMsg(L, ERROR_MSG, MsgFormat(@"options.userId (string) expected, got: %s", luaL_typename(L, -1)));
					return 0;
				}
			}
			else {
				logMsg(L, ERROR_MSG, MsgFormat(@"Invalid option '%s'", key));
				return 0;
			}
		}
	}
	// no options table
	else {
		logMsg(L, ERROR_MSG, MsgFormat(@"options table expected, got %s", luaL_typename(L, 1)));
		return 0;
	}
	
	// validate gender
	AppodealUserGender appodealGender = AppodealUserGenderOther;
	
	if (gender != NULL) {
		if (UTF8IsEqual(gender, GENDER_FEMALE)) {
			appodealGender = AppodealUserGenderFemale;
		}
		else if (UTF8IsEqual(gender, GENDER_MALE)) {
			appodealGender = AppodealUserGenderMale;
		}
		else if (UTF8IsEqual(gender, GENDER_OTHER)) {
			appodealGender = AppodealUserGenderOther;
		}
		else {
			logMsg(L, ERROR_MSG, MsgFormat(@"'%s', invalid gender", gender));
			return 0;
		}
	}
	
	// set user settings
	if (userId != NULL) {
		[Appodeal setUserId:@(userId)];
	}
	
	if (age != NO_VALUE) {
		//[Appodeal setUserAge:age];
	}
	
	if (gender != NULL) {
		//[Appodeal setUserGender:appodealGender];
	}
	
	return 0;
}

// ----------------------------------------------------------------------------
// delegate implementation
// ----------------------------------------------------------------------------

@implementation AppodealPluginDelegate

- (instancetype)init {
	if (self = [super init]) {
		self.coronaListener = NULL;
		self.coronaRuntime = NULL;
		self.sdkInitialized = false;
	}
	
	return self;
}

// dispatch a new Lua event
- (void)dispatchLuaEvent:(NSDictionary *)dict
{
	[[NSOperationQueue mainQueue] addOperationWithBlock:^{
		lua_State *L = self.coronaRuntime.L;
		CoronaLuaRef coronaListener = self.coronaListener;
		bool hasErrorKey = false;
		
		// create new event
		CoronaLuaNewEvent(L, EVENT_NAME);
		
		for (NSString *key in dict) {
			CoronaLuaPushValue(L, [dict valueForKey:key]);
			lua_setfield(L, -2, key.UTF8String);
			
			if (! hasErrorKey) {
				hasErrorKey = [key isEqualToString:@(CoronaEventIsErrorKey())];
			}
		}
		
		// add error key if not in dict
		if (! hasErrorKey) {
			lua_pushboolean(L, false);
			lua_setfield(L, -2, CoronaEventIsErrorKey());
		}
		
		// add provider
		lua_pushstring(L, PROVIDER_NAME );
		lua_setfield(L, -2, CoronaEventProviderKey());
		
		CoronaLuaDispatchEvent(L, coronaListener, 0);
	}];
}

// Banner delegate methods
// ----------------------------------------------------------------------------
- (void)bannerDidLoadAdIsPrecache:(BOOL)precache
{
	NSDictionary *data = @{
		@"height": @(0),
		@"isPrecache": @(precache)
	};
	
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_LOADED,
		@(CoronaEventTypeKey()): @(TYPE_BANNER),
		@(CoronaEventDataKey()): data
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)bannerDidFailToLoadAd
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_FAILED,
		@(CoronaEventTypeKey()): @(TYPE_BANNER),
		@(CoronaEventResponseKey()): RESPONSE_LOADFAILED,
		@(CoronaEventIsErrorKey()): @(true)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)bannerDidClick
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_CLICKED,
		@(CoronaEventTypeKey()): @(TYPE_BANNER)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)bannerDidShow
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_DISPLAYED,
		@(CoronaEventTypeKey()): @(TYPE_BANNER)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)bannerDidRefresh
{
	// The Appodeal SDK for Android sends a 'didShow' event upon refresh
	// we mimic that behavior here.
	[self bannerDidShow];
}

// Interstitial delegate methods
// ----------------------------------------------------------------------------
-(void)interstitialDidLoadAdIsPrecache:(BOOL)precache
{
	NSDictionary *data = @{
		@"isPrecache": @(precache)
	};
	
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_LOADED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL),
		@(CoronaEventDataKey()): data
	};
	[self dispatchLuaEvent:coronaEvent];
	
}

- (void)interstitialDidFailToLoadAd
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_FAILED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL),
		@(CoronaEventResponseKey()): RESPONSE_LOADFAILED,
		@(CoronaEventIsErrorKey()): @(true)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)interstitialWillPresent
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_DISPLAYED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)interstitialDidDismiss
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_CLOSED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)interstitialDidClick
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_CLICKED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)interstitialDidFailToPresent
{
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_FAILED,
		@(CoronaEventTypeKey()): @(TYPE_INTERSTITIAL),
		@(CoronaEventResponseKey()): RESPONSE_PRESENTFAILED,
		@(CoronaEventIsErrorKey()): @(true)
	};
	[self dispatchLuaEvent:coronaEvent];
}

// Rewarded video delegate methods
// ----------------------------------------------------------------------------
- (void)rewardedVideoDidLoadAdIsPrecache:(BOOL)precache
{
	NSDictionary *data = @{
		@"loaded": @(precache)
	};
	
	// send Corona Lua event
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_LOADED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		@(CoronaEventDataKey()): data
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoDidFailToLoadAd
{
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_FAILED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		@(CoronaEventResponseKey()): RESPONSE_LOADFAILED,
		@(CoronaEventIsErrorKey()): @(true)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoDidPresent
{
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_PLAYBACK_BEGAN,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO)
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoWillDismissAndWasFullyWatched:(BOOL)wasFullyWatched
{
	NSDictionary *data = @{
		@"finished": @(wasFullyWatched)
	};
	
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_CLOSED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		@(CoronaEventDataKey()): data
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoDidFinish:(float)rewardAmount name:(NSString *)rewardName
{
	// Create the reward data
	NSDictionary *rewardData = @{
		REWARD_AMOUNT_KEY: [NSNumber numberWithFloat:rewardAmount],
		REWARD_NAME_KEY: (rewardName != nil) ? rewardName : @"reward"
	};
	
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_PLAYBACK_ENDED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		CORONA_EVENT_DATA_KEY: rewardData
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoDidClick
{
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_CLICKED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
	};
	[self dispatchLuaEvent:coronaEvent];
}

- (void)rewardedVideoDidFailToPresent
{
	NSDictionary *coronaEvent = @{
		@(CoronaEventPhaseKey()): PHASE_FAILED,
		@(CoronaEventTypeKey()): @(TYPE_REWARDEDVIDEO),
		@(CoronaEventResponseKey()): RESPONSE_PRESENTFAILED,
		@(CoronaEventIsErrorKey()): @(true)
	};
	[self dispatchLuaEvent:coronaEvent];
}

@end

//----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_plugin_appodeal(lua_State *L)
{
	return AppodealLibrary::Open(L);
}
