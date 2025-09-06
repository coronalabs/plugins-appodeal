//
// LuaLoader.java
// Appodeal Plugin
// Copyright (c) 2016 CoronaLabs inc. All rights reserved.
//


package plugin.appodeal;

import android.util.Log;
import android.util.Pair;

import com.ansca.corona.CoronaActivity;
import com.ansca.corona.CoronaEnvironment;
import com.ansca.corona.CoronaLua;
import com.ansca.corona.CoronaLuaEvent;
import com.ansca.corona.CoronaRuntime;
import com.ansca.corona.CoronaRuntimeListener;
import com.ansca.corona.CoronaRuntimeTask;
import com.ansca.corona.CoronaRuntimeTaskDispatcher;
import com.appodeal.ads.Appodeal;
import com.appodeal.ads.BannerCallbacks;
import com.appodeal.ads.InterstitialCallbacks;
import com.appodeal.ads.RewardedVideoCallbacks;
import com.appodeal.ads.UserSettings;
import com.appodeal.ads.initializing.ApdInitializationCallback;
import com.appodeal.ads.initializing.ApdInitializationError;
import com.appodeal.ads.rewarded.Reward;
import com.naef.jnlua.JavaFunction;
import com.naef.jnlua.LuaState;
import com.naef.jnlua.LuaType;
import com.naef.jnlua.NamedJavaFunction;

import org.json.JSONArray;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

// Appodeal provider imports

/**
 * Implements the Lua interface for the plugin.
 * <p>
 * Only one instance of this class will be created by Corona for the lifetime of the application.
 * This instance will be re-used for every new Corona activity that gets created.
 */
@SuppressWarnings({"unused", "RedundantSuppression"})
public class LuaLoader implements JavaFunction, CoronaRuntimeListener {
    private static final String PLUGIN_NAME = "plugin.appodeal";
    private static final String PLUGIN_VERSION = "1.6.7";
    private static final String PLUGIN_SDK_VERSION = Appodeal.getVersion();

    private static final String EVENT_NAME = "adsRequest";
    private static final String PROVIDER_NAME = "appodeal";

    // ad types
    private static final String TYPE_BANNER = "banner";
    private static final String TYPE_INTERSTITIAL = "interstitial";
    private static final String TYPE_REWARDEDVIDEO = "rewardedVideo";

    // gender types
    private static final String GENDER_MALE = "male";
    private static final String GENDER_FEMALE = "female";
    private static final String GENDER_OTHER = "other";

    // valid ad types
    private static final List<String> validAdTypes = new ArrayList<>();

    // banner alignment
    private static final String BANNER_ALIGN_TOP = "top";
    private static final String BANNER_ALIGN_BOTTOM = "bottom";

    // event phases
    private static final String PHASE_INIT = "init";
    private static final String PHASE_DISPLAYED = "displayed";
    private static final String PHASE_LOADED = "loaded";
    private static final String PHASE_FAILED = "failed";
    private static final String PHASE_CLOSED = "closed";
    private static final String PHASE_CLICKED = "clicked";
    private static final String PHASE_PLAYBACK_BEGAN = "playbackBegan";
    private static final String PHASE_PLAYBACK_ENDED = "playbackEnded";
    private static final String PHASE_HIDDEN = "hidden";
    private static final String PHASE_DATA_RECEIVED = "dataReceived";
    private static final String PHASE_REFRESH = "refresh";

    private static final String PHASE_SHOWN = "shown";
    private static final String PHASE_EXPIRED = "expired";

    // add missing keys
    private static final String EVENT_PHASE_KEY = "phase";
    private static final String EVENT_TYPE_KEY = "type";
    private static final String EVENT_DATA_KEY = "data";

    // response codes
    private static final String RESPONSE_LOADFAILED = "failed to load";

    // data keys
    private static final String REWARD_AMOUNT_KEY = "amount";
    private static final String REWARD_NAME_KEY = "name";

    // message constants
    private static final String CORONA_TAG = "Corona";
    private static final String ERROR_MSG = "ERROR: ";
    private static final String WARNING_MSG = "WARNING: ";
    // object dictionary keys
    private static final String SUPPORTED_ADTYPES_KEY = "supportedAdTypes";
    private static final String AUTOCACHE_KEY = "autoCache";
    private static final int NO_VALUE = Integer.MAX_VALUE;
    private static final int NO_ADTYPE = 0;
    // saved objects (apiKey, ad state, etc)
    private static final Map<String, Object> appodealObjects = new HashMap<>();
    private static String functionSignature = "";                                  // used in error reporting functions
    private CoronaRuntimeTaskDispatcher coronaRuntimeTaskDispatcher;
    private int coronaListener = CoronaLua.REFNIL;
    private Boolean sdkInitialized = false;

    // -------------------------------------------------------------------
    // Plugin lifecycle events
    // -------------------------------------------------------------------

    /**
     * <p>
     * Note that a new LuaLoader instance will not be created for every CoronaActivity instance.
     * That is, only one instance of this class will be created for the lifetime of the application process.
     * This gives a plugin the option to do operations in the background while the CoronaActivity is destroyed.
     */
    public LuaLoader() {
        // Set up this plugin to listen for Corona runtime events to be received by methods
        // onLoaded(), onStarted(), onSuspended(), onResumed(), and onExiting().
        CoronaEnvironment.addRuntimeListener(this);
    }

    /**
     * Called when this plugin is being loaded via the Lua require() function.
     * <p>
     * Note that this method will be called everytime a new CoronaActivity has been launched.
     * This means that you'll need to re-initialize this plugin here.
     * <p>
     * Warning! This method is not called on the main UI thread.
     *
     * @param L Reference to the Lua state that the require() function was called from.
     * @return Returns the number of values that the require() function will return.
     * <p>
     * Expected to return 1, the library that the require() function is loading.
     */
    @Override
    public int invoke(LuaState L) {
        // Register this plugin into Lua with the following functions.
        NamedJavaFunction[] luaFunctions = new NamedJavaFunction[]
                {
                        new Init(),
                        new Show(),
                        new Hide(),
                        new Load(),
                        new IsLoaded(),
                        new SetUserDetails(),
                        new GetRewardParameters(),
                        new GetVersion(),
                        new CanShow(),
                        new SetSegmentFilter(),
                        new TrackInAppPurchase(),
                        new Set728x90Banners()
                };
        String libName = L.toString(1);
        L.register(libName, luaFunctions);

        // Returning 1 indicates that the Lua require() function will return the above Lua
        return 1;
    }

    /**
     * Called after the Corona runtime has been created and just before executing the "main.lua" file.
     * <p>
     * Warning! This method is not called on the main thread.
     *
     * @param runtime Reference to the CoronaRuntime object that has just been loaded/initialized.
     *                Provides a LuaState object that allows the application to extend the Lua API.
     */
    @Override
    public void onLoaded(CoronaRuntime runtime) {
        // Note that this method will not be called the first time a Corona activity has been launched.
        // This is because this listener cannot be added to the CoronaEnvironment until after
        // this plugin has been required-in by Lua, which occurs after the onLoaded() event.
        // However, this method will be called when a 2nd Corona activity has been created.
        if (coronaRuntimeTaskDispatcher == null) {
            coronaRuntimeTaskDispatcher = new CoronaRuntimeTaskDispatcher(runtime);

            // initialize list values
            validAdTypes.add(TYPE_BANNER);
            validAdTypes.add(TYPE_INTERSTITIAL);
            validAdTypes.add(TYPE_REWARDEDVIDEO);
        }
    }

    /**
     * Called just after the Corona runtime has executed the "main.lua" file.
     * <p>
     * Warning! This method is not called on the main thread.
     *
     * @param runtime Reference to the CoronaRuntime object that has just been started.
     */
    @Override
    public void onStarted(CoronaRuntime runtime) {
    }

    /**
     * Called just after the Corona runtime has been suspended which pauses all rendering, audio, timers,
     * and other Corona related operations. This can happen when another Android activity (ie: window) has
     * been displayed, when the screen has been powered off, or when the screen lock is shown.
     * <p>
     * Warning! This method is not called on the main thread.
     *
     * @param runtime Reference to the CoronaRuntime object that has just been suspended.
     */
    @Override
    public void onSuspended(CoronaRuntime runtime) {
    }

    /**
     * Called just after the Corona runtime has been resumed after a suspend.
     * <p>
     * Warning! This method is not called on the main thread.
     *
     * @param runtime Reference to the CoronaRuntime object that has just been resumed.
     */
    @Override
    public void onResumed(CoronaRuntime runtime) {
    }

    /**
     * Called just before the Corona runtime terminates.
     * <p>
     * This happens when the Corona activity is being destroyed which happens when the user presses the Back button
     * on the activity, when the native.requestExit() method is called in Lua, or when the activity's finish()
     * method is called. This does not mean that the application is exiting.
     * <p>
     * Warning! This method is not called on the main thread.
     *
     * @param runtime Reference to the CoronaRuntime object that is being terminated.
     */
    @Override
    public void onExiting(CoronaRuntime runtime) {
        // clear callbacks
        Appodeal.setBannerCallbacks(null);
        Appodeal.setInterstitialCallbacks(null);
        Appodeal.setRewardedVideoCallbacks(null);

        // Remove the Lua listener reference.
        CoronaLua.deleteRef(runtime.getLuaState(), coronaListener);
        coronaListener = CoronaLua.REFNIL;

        coronaRuntimeTaskDispatcher = null;
        validAdTypes.clear();
        appodealObjects.clear();
        sdkInitialized = false;
    }

    // -------------------------------------------------------------------
    // helper functions
    // -------------------------------------------------------------------

    // log message to console
    private void logMsg(String msgType, String errorMsg) {
        String functionID = functionSignature;
        if (!functionID.isEmpty()) {
            functionID += ", ";
        }

        Log.i(CORONA_TAG, msgType + functionID + errorMsg);
    }

    private void setRules(Hashtable<Object, Object> customRules) {
        // set the custom rules
        if (customRules != null) {
            for (Object objKey : customRules.keySet()) {
                String key = (String) objKey;
                Object value = customRules.get(objKey);
                Appodeal.setCustomFilter(key, value);
            }
        }
    }

    // return true if SDK is properly initialized
    @SuppressWarnings("BooleanMethodIsAlwaysInverted")
    private boolean isSDKInitialized() {
        if (coronaListener == CoronaLua.REFNIL) {
            logMsg(ERROR_MSG, "appodeal.init() must be called before calling other API functions");
            return false;
        }

        if (!sdkInitialized) {
            logMsg(ERROR_MSG, "appodeal.init() was called with incorrect parameters");
            return false;
        }

        return true;
    }

    // dispatch a Lua event to our callback (dynamic handling of properties through map)
    private void dispatchLuaEvent(final Map<String, Object> event) {
        if (coronaRuntimeTaskDispatcher != null) {
            coronaRuntimeTaskDispatcher.send(new CoronaRuntimeTask() {
                @Override
                public void executeUsing(CoronaRuntime runtime) {
                    try {
                        LuaState L = runtime.getLuaState();
                        CoronaLua.newEvent(L, EVENT_NAME);
                        boolean hasErrorKey = false;

                        // add event parameters from map
                        for (String key : event.keySet()) {
                            CoronaLua.pushValue(L, event.get(key));           // push value
                            L.setField(-2, key);                              // push key

                            if (!hasErrorKey) {
                                hasErrorKey = key.equals(CoronaLuaEvent.ISERROR_KEY);
                            }
                        }

                        // add error key if not in map
                        if (!hasErrorKey) {
                            L.pushBoolean(false);
                            L.setField(-2, CoronaLuaEvent.ISERROR_KEY);
                        }

                        // add provider
                        L.pushString(PROVIDER_NAME);
                        L.setField(-2, CoronaLuaEvent.PROVIDER_KEY);

                        CoronaLua.dispatchEvent(L, coronaListener, 0);
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
            });
        }
    }

    // Check available modules
    private void checkAvailableModules() {

        if(isSDKInitialized()) {
            Log.w(CORONA_TAG, "Too late to disable modules!");
        }

//            com.appodeal.ads.adapters.a4g.R
//            com.appodeal.ads.adapters.admob.R;
//            com.appodeal.ads.adapters.applovin.R;
//            com.appodeal.ads.adapters.bidmachine.R;
//            com.appodeal.ads.adapters.meta.R;
//            com.appodeal.ads.adapters.ironsource.R;
//            com.appodeal.ads.adapters.mytarget.R;
//            com.appodeal.ads.adapters.notsy.R;
//            com.appodeal.ads.adapters.unityads.R;
//            com.appodeal.ads.adapters.vungle.R;
//            com.appodeal.ads.adapters.yandex.R;

//            try {
//                Class.forName("com.appodeal.ads.ada");
//            } catch (ClassNotFoundException e) {
//                Appodeal.disableNetwork("adcolony");
//            }
    }

    // -------------------------------------------------------------------
    // Plugin implementation
    // -------------------------------------------------------------------

    // [Lua] appodeal.init(listener, options)
    @SuppressWarnings("IfCanBeSwitch")
    private class Init implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "init";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.init(listener, options)";

            // prevent init from being called twice
            if (coronaListener != CoronaLua.REFNIL) {
                logMsg(WARNING_MSG, "init() should only be called once");
                return 0;
            }

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 2) {
                logMsg(ERROR_MSG, "Expected 2 arguments, got " + nargs);
                return 0;
            }

            String appKey = null;
            boolean testMode = false;
            ArrayList<String> dAutoCacheAdTypes = new ArrayList<>();
            boolean smartBanners = true;
            boolean bannerAnimation = false;
            boolean childDirectedTreatmentIsSet = false;
            Boolean childDirectedTreatmentSetting = null;
            boolean locationTracking = false;
            boolean showInOtherWindow = false;
            boolean disableOnscreenFocusCheck = true;
            boolean disableWriteExternalPermissionCheck = false;
            ArrayList<String> supportedAdTypes = new ArrayList<>();
            final ArrayList<String> disabledAdNetworks = new ArrayList<>();
            Hashtable<Object, Object> customRules = null;
            boolean hasUserConsent = true;

            // Get listener key (required)
            if (CoronaLua.isListener(luaState, 1, PROVIDER_NAME)) {
                coronaListener = CoronaLua.newRef(luaState, 1);
            } else {
                logMsg(ERROR_MSG, "listener expected, got: " + luaState.typeName(1));
                return 0;
            }

            // check for options table (required)
            if (luaState.type(2) == LuaType.TABLE) {
                // traverse and verify all options
                for (luaState.pushNil(); luaState.next(2); luaState.pop(1)) {
                    String key = luaState.toString(-2);

                    if (key.equals("appKey")) {
                        if (luaState.type(-1) == LuaType.STRING) {
                            appKey = luaState.toString(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.appKey (string) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("testMode")) {
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            testMode = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.testMode (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("disableAutoCacheForAdTypes")) {
                        if (luaState.type(-1) == LuaType.TABLE) {
                            // build supported ad types
                            int ntypes = luaState.length(-1);

                            if (ntypes > 0) {
                                for (int i = 1; i <= ntypes; i++) {
                                    // push array value onto stack
                                    luaState.rawGet(-1, i);

                                    // add ad type to array
                                    if (luaState.type(-1) == LuaType.STRING) {
                                        dAutoCacheAdTypes.add(luaState.toString(-1));
                                    } else {
                                        logMsg(ERROR_MSG, "options.disableAutoCacheForAdTypes[" + i + "] (string) expected, got: " + luaState.typeName(-1));
                                        return 0;
                                    }
                                    luaState.pop(1);
                                }
                            } else {
                                logMsg(ERROR_MSG, "options.disableAutoCacheForAdTypes table cannot be empty");
                                return 0;
                            }
                        } else {
                            logMsg(ERROR_MSG, "options.supportedAdType (table) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("showInOtherWindow")) { // undocumented internal option
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            showInOtherWindow = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.showInOtherWindow (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("disableOnscreenFocusCheck")) { // undocumented internal option
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            disableOnscreenFocusCheck = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.disableOnscreenFocusCheck (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("smartBanners")) {
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            smartBanners = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.smartBanners (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("disableWriteExternalPermissionCheck")) {
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            disableWriteExternalPermissionCheck = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.disableWriteExternalPermissionCheck (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("bannerAnimation")) {
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            bannerAnimation = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.bannerAnimation (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("childDirectedTreatment")) {
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            childDirectedTreatmentIsSet = true;
                            childDirectedTreatmentSetting = luaState.toBoolean(-1);
                        } else if (luaState.type(-1) == LuaType.STRING && (luaState.toString(-1).equals("null") || luaState.toString(-1).equals("nil"))) {
                            childDirectedTreatmentIsSet = true;
                            childDirectedTreatmentSetting = null;
                        } else {
                            logMsg(ERROR_MSG, "options.childDirectedTreatment (boolean) or string constant 'null' or 'nil' expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("locationTracking")) {
                        // This is iOS only as location tracking is set by permissions on Android
                        // we just validate here, nothing else
                        if (luaState.type(-1) == LuaType.BOOLEAN) {
                            locationTracking = luaState.toBoolean(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.locationTracking (boolean) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("customRules")) {
                        if (luaState.type(-1) == LuaType.TABLE) {
                            customRules = CoronaLua.toHashtable(luaState, -1);
                        } else {
                            logMsg(ERROR_MSG, "options.customRules (table) expected, got " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("supportedAdTypes")) {
                        if (luaState.type(-1) == LuaType.TABLE) {
                            // build supported ad types
                            int ntypes = luaState.length(-1);

                            if (ntypes > 0) {
                                for (int i = 1; i <= ntypes; i++) {
                                    // push array value onto stack
                                    luaState.rawGet(-1, i);

                                    // add ad type to array
                                    if (luaState.type(-1) == LuaType.STRING) {
                                        supportedAdTypes.add(luaState.toString(-1));
                                    } else {
                                        logMsg(ERROR_MSG, "options.supportedAdTypes[" + i + "] (string) expected, got: " + luaState.typeName(-1));
                                        return 0;
                                    }
                                    luaState.pop(1);
                                }
                            } else {
                                logMsg(ERROR_MSG, "options.supportedAdTypes table cannot be empty");
                                return 0;
                            }
                        } else {
                            logMsg(ERROR_MSG, "options.supportedAdType (table) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("disableNetworks")) { // for internal use only (developers should disable networks from the dashboard)
                        if (luaState.type(-1) == LuaType.TABLE) {
                            // build supported ad types
                            int ntypes = luaState.length(-1);

                            if (ntypes > 0) {
                                for (int i = 1; i <= ntypes; i++) {
                                    // push array value onto stack
                                    luaState.rawGet(-1, i);

                                    // add ad type to array
                                    if (luaState.type(-1) == LuaType.STRING) {
                                        disabledAdNetworks.add(luaState.toString(-1));
                                    } else {
                                        logMsg(ERROR_MSG, "options.disabledNetworks[" + i + "] (string) expected, got: " + luaState.typeName(-1));
                                        return 0;
                                    }
                                    luaState.pop(1);
                                }
                            } else {
                                logMsg(ERROR_MSG, "options.disabledNetworks table cannot be empty");
                                return 0;
                            }
                        } else {
                            logMsg(ERROR_MSG, "options.disabledNetworks (table) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("hasUserConsent")) {
                        logMsg(WARNING_MSG, "options.hasUserConsent has been removed");
                    } else if (key.equals("autoCacheAds")) {
                        logMsg(ERROR_MSG, "Parameter autoCacheAds was deprecated. Use disableAutoCacheForAdTypes instead");
                        return 0;
                    } else {
                        logMsg(ERROR_MSG, "Invalid option '" + key + "'");
                        return 0;
                    }
                }
            }
            // no options table
            else {
                logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(2));
                return 0;
            }

            // validate appKey
            if (appKey == null) {
                logMsg(ERROR_MSG, "options.appKey missing");
                return 0;
            }

            // simple customRules key/value validation
            if (customRules != null) {
                for (Object objKey : customRules.keySet()) {
                    if (objKey instanceof Double) {
                        logMsg(ERROR_MSG, "options.customRules must be a key/value table");
                        return 0;
                    }
                }
            }

            // validate supported ad types
            int adTypes = NO_ADTYPE;

            for (Iterator<String> adTypeIterator = supportedAdTypes.iterator(); adTypeIterator.hasNext(); ) {
                String adType = adTypeIterator.next();
                if (!validAdTypes.contains(adType)) {
                    logMsg(ERROR_MSG, "Invalid supportedAdType '" + adType + '"');
                    return 0;
                }

                if (adType.equals(TYPE_BANNER)) {
                    adTypes |= Appodeal.BANNER;
                } else if (adType.equals(TYPE_INTERSTITIAL)) {
                    adTypes |= Appodeal.INTERSTITIAL;
                } else if (adType.equals(TYPE_REWARDEDVIDEO)) {
                    adTypes |= Appodeal.REWARDED_VIDEO;
                }
            }

            // default to all ad types if none given
            if (adTypes == NO_ADTYPE) {
                adTypes = Appodeal.BANNER | Appodeal.INTERSTITIAL | Appodeal.REWARDED_VIDEO;
                supportedAdTypes.add(TYPE_BANNER);
                supportedAdTypes.add(TYPE_INTERSTITIAL);
                supportedAdTypes.add(TYPE_REWARDEDVIDEO);
            }

            // validate supported ad types
            int dAdTypes = NO_ADTYPE;

            for (Iterator<String> adTypeIterator = dAutoCacheAdTypes.iterator(); adTypeIterator.hasNext(); ) {
                String adType = adTypeIterator.next();
                if (!validAdTypes.contains(adType)) {
                    logMsg(ERROR_MSG, "Invalid dAutoCacheAdTypes '" + adType + '"');
                    return 0;
                }

                if (adType.equals(TYPE_BANNER)) {
                    dAdTypes |= Appodeal.BANNER;
                } else if (adType.equals(TYPE_INTERSTITIAL)) {
                    dAdTypes |= Appodeal.INTERSTITIAL;
                } else if (adType.equals(TYPE_REWARDEDVIDEO)) {
                    dAdTypes |= Appodeal.REWARDED_VIDEO;
                }
            }

            // default to all ad types if none given
            if (adTypes == NO_ADTYPE) {
                adTypes = 0;
            }

            // save data for future use
            appodealObjects.put(SUPPORTED_ADTYPES_KEY, supportedAdTypes);
            appodealObjects.put(AUTOCACHE_KEY, dAutoCacheAdTypes);

            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
            final String fAppKey = appKey;
            final boolean fTestMode = testMode;
            final boolean fSmartBanners = smartBanners;
            final boolean fBannerAnimation = bannerAnimation;
            final Boolean fChildDirectedTreatmentSetting = childDirectedTreatmentSetting;
            final boolean fChildDirectedTreatmentIsSet = childDirectedTreatmentIsSet;
            final int fdAutoCacheAdTypes = dAdTypes;
            final boolean fShowInOtherWindow = showInOtherWindow;
            final boolean fDisableWriteExternalPermissionCheck = disableWriteExternalPermissionCheck;
            final boolean fDisableOnscreenFocusCheck = disableOnscreenFocusCheck;
            final Hashtable<Object, Object> fCustomRules = customRules;
            final int fAdTypes = adTypes;

            if (coronaActivity != null) {
                Runnable runnableActivity = new Runnable() {
                    public void run() {

                        Appodeal.setAutoCache(fdAutoCacheAdTypes, false);
                        Appodeal.setBannerAnimation(fBannerAnimation);
                        Appodeal.setSmartBanners(fSmartBanners);
                        if (fChildDirectedTreatmentIsSet) {
                            Appodeal.setChildDirectedTreatment(fChildDirectedTreatmentSetting);
                        }

                        // the last two booleans are internal settings for banner performance testing
                        Appodeal.setFramework(CORONA_TAG, PLUGIN_VERSION);

                        // set the custom rules
                        if (fCustomRules != null) {
                            setRules(fCustomRules);
                        }

                        // disable ad networks (for advanced use only)
                        // developers should normally disable networks from their Appodeal dashboard
                        if (disabledAdNetworks.size() > 0) {
                            for (String adNetwork : disabledAdNetworks) {
                                Log.i(CORONA_TAG, "Disabling ad network " + adNetwork + " (WARNING: FOR ADVANCED USE ONLY. DO NOT USE UNLESS YOU KNOW WHAT YOU ARE DOING)");
                                Appodeal.disableNetwork(adNetwork);
                            }
                        }

                        // set testing mode
                        if (fTestMode) {
                            Appodeal.setTesting(true);
                            Appodeal.setLogLevel(com.appodeal.ads.utils.Log.LogLevel.verbose);
                        }

                        checkAvailableModules();

                        // initialize sdk
                        Appodeal.initialize(coronaActivity, fAppKey, fAdTypes, new ApdInitializationCallback() {
                            @Override
                            public void onInitializationFinished(List<ApdInitializationError> errors) {
                                HashMap<String, Object> event = new HashMap<>();
                                event.put(EVENT_PHASE_KEY, PHASE_INIT);

                                if(errors != null) {
                                    event.put(CoronaLuaEvent.ISERROR_KEY, true);
                                    JSONArray array = new JSONArray();
                                    for (ApdInitializationError e : errors) {
                                        array.put(e.getLocalizedMessage());
                                    }
                                    event.put(CoronaLuaEvent.RESPONSE_KEY, array.toString());
                                }
                                dispatchLuaEvent(event);
                            }
                        });

                        Appodeal.setBannerCallbacks(new AppodealBannerDelegate());
                        Appodeal.setInterstitialCallbacks(new AppodealInterstitialDelegate());
                        Appodeal.setRewardedVideoCallbacks(new AppodealRewardedVideoDelegate());
                        Appodeal.setFramework("Corona", "1.0.0");
                    }
                };

                coronaActivity.runOnUiThread(runnableActivity);
            }

            // log plugin version to device console
            Log.i(CORONA_TAG, PLUGIN_NAME + ": " + PLUGIN_VERSION + " (SDK: " + PLUGIN_SDK_VERSION + ")");
            Log.d("Appodeal", "This is Corona/Solar2D Appodeal plugin");

            sdkInitialized = true;

            return 0;
        }
    }

    private class LogEvent implements NamedJavaFunction {

        @Override
        public String getName() {
            return "logEvent";
        }

        @Override
        public int invoke(LuaState luaState) {
            if (!isSDKInitialized()) {
                return 0;
            }
            String name = luaState.toString(1);
            HashMap<String, Object> params = new HashMap<>();
            if(luaState.isTable(2)) {
                for (luaState.pushNil(); luaState.next(2); luaState.pop(1)) {
                    String key = luaState.toString(-2);
                    Object value = CoronaLua.toValue(luaState, -1);
                    params.put(key, value);
                }
            }
            Appodeal.logEvent(name, params);
            return 0;
        }
    }

    // [Lua] appodeal.show(adUnitType [, options])
    private class Show implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "show";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.show(adUnitType [, options])";

            if (!isSDKInitialized()) {
                return 0;
            }

            // get number of arguments
            int nargs = luaState.getTop();
            if ((nargs < 1) || (nargs > 2)) {
                logMsg(ERROR_MSG, "Expected 1 or 2 arguments, got " + nargs);
                return 0;
            }

            String adUnitType = null;
            String yAlign = BANNER_ALIGN_BOTTOM;
            String placement = null;

            // Ensure the adUnitType is a string
            if (luaState.type(1) == LuaType.STRING) {
                adUnitType = luaState.toString(1);
            } else {
                logMsg(ERROR_MSG, "adUnitType (string) expected, got: " + luaState.typeName(1));
                return 0;
            }

            if (!luaState.isNoneOrNil(2)) {
                // check for options table
                if (luaState.type(2) == LuaType.TABLE) {
                    // traverse and verify all options
                    for (luaState.pushNil(); luaState.next(2); luaState.pop(1)) {
                        String key = luaState.toString(-2);

                        if (key.equals("yAlign")) {
                            if (luaState.type(-1) == LuaType.STRING) {
                                yAlign = luaState.toString(-1);
                            } else {
                                logMsg(ERROR_MSG, "options.yAlign (string) expected, got: " + luaState.typeName(-1));
                                return 0;
                            }
                        } else if (key.equals("placement")) {
                            if (luaState.type(-1) == LuaType.STRING) {
                                placement = luaState.toString(-1);
                            } else {
                                logMsg(ERROR_MSG, "options.placement (string) expected, got: " + luaState.typeName(-1));
                                return 0;
                            }
                        } else {
                            logMsg(ERROR_MSG, "Invalid option '" + key + "'");
                            return 0;
                        }
                    }
                }
                // no options table
                else {
                    logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(2));
                    return 0;
                }
            }

            // validate ad unit type
            if (!validAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Invalid adUnitType '" + adUnitType + "'");
                return 0;
            }

            // make sure ad unit type was specified during init()
            ArrayList<String> supportedAdTypes = (ArrayList<String>) appodealObjects.get(SUPPORTED_ADTYPES_KEY);
            if (!supportedAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // validate yAlign
            if ((!yAlign.equals(BANNER_ALIGN_BOTTOM)) && (!yAlign.equals(BANNER_ALIGN_TOP))) {
                logMsg(ERROR_MSG, "Invalid yAlign '" + yAlign + "'");
                return 0;
            }

            // declare final vars for inner loop
            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
            final String fAdUnitType = adUnitType;
            final String fYAlign = yAlign;
            final String fPlacement = placement;

            if (coronaActivity != null) {
                Runnable runnableActivity = new Runnable() {
                    public void run() {
                        int showStyle = NO_VALUE;

                        if (fAdUnitType.equals(TYPE_BANNER)) {
                            showStyle = fYAlign.equals(BANNER_ALIGN_BOTTOM) ? Appodeal.BANNER_BOTTOM : Appodeal.BANNER_TOP;
                        } else if (fAdUnitType.equals(TYPE_INTERSTITIAL)) {
                            showStyle = Appodeal.INTERSTITIAL;
                        } else if (fAdUnitType.equals(TYPE_REWARDEDVIDEO)) {
                            showStyle = Appodeal.REWARDED_VIDEO;
                        }

//            // do we have a placement?
//            if (fPlacement == null) {
//              Appodeal.show(coronaActivity, showStyle);
//            }
//            else {
//              Appodeal.show(coronaActivity, showStyle, fPlacement);
//            }

                        // do we have a placement?
                        if (fPlacement == null) {
                            if (showStyle == Appodeal.REWARDED_VIDEO && Appodeal.show(coronaActivity, showStyle)) {
                                Map<String, Object> event = new HashMap<>();
                                event.put(EVENT_PHASE_KEY, PHASE_PLAYBACK_BEGAN);
                                event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
                                dispatchLuaEvent(event);
                            } else if (showStyle == Appodeal.INTERSTITIAL && Appodeal.show(coronaActivity, showStyle)) {
                                Map<String, Object> event = new HashMap<>();
                                event.put(EVENT_PHASE_KEY, PHASE_DISPLAYED);
                                event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
                                dispatchLuaEvent(event);
                            } else {
                                Appodeal.show(coronaActivity, showStyle);
                            }
                        } else {

                            if (showStyle == Appodeal.REWARDED_VIDEO && Appodeal.show(coronaActivity, showStyle, fPlacement)) {
                                Map<String, Object> event = new HashMap<>();
                                event.put(EVENT_PHASE_KEY, PHASE_PLAYBACK_BEGAN);
                                event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
                                dispatchLuaEvent(event);
                            } else if (showStyle == Appodeal.INTERSTITIAL && Appodeal.show(coronaActivity, showStyle, fPlacement)) {
                                Map<String, Object> event = new HashMap<>();
                                event.put(EVENT_PHASE_KEY, PHASE_DISPLAYED);
                                event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
                                dispatchLuaEvent(event);
                            } else {
                                Appodeal.show(coronaActivity, showStyle, fPlacement);
                            }
                        }
                    }
                };

                // Run the activity on the uiThread
                coronaActivity.runOnUiThread(runnableActivity);
            }

            return 0;
        }
    }

    // [Lua] appodeal.hide(adUnitType)
    private class Hide implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "hide";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.hide(adUnitType)";

            if (!isSDKInitialized()) {
                return 0;
            }

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got " + nargs);
                return 0;
            }

            String adUnitType = null;

            // Ensure the adUnitType is a string
            if (luaState.type(1) == LuaType.STRING) {
                adUnitType = luaState.toString(1);
            } else {
                logMsg(ERROR_MSG, "adUnitType (string) expected, got: " + luaState.typeName(1));
                return 0;
            }

            // validate ad unit type
            if (!adUnitType.equals(TYPE_BANNER)) {
                logMsg(ERROR_MSG, "adUnitType='" + adUnitType + "'. Only banners can be hidden");
                return 0;
            }

            // make sure ad unit type was specified during init()
            ArrayList<String> supportedAdTypes = (ArrayList<String>) appodealObjects.get(SUPPORTED_ADTYPES_KEY);
            if (!supportedAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // declare final vars for inner loop
            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
            final String fAdUnitType = adUnitType;

            if (coronaActivity != null) {
                Runnable runnableActivity = new Runnable() {
                    public void run() {
                        Appodeal.hide(coronaActivity, Appodeal.BANNER);

                        // Dispatch the Lua event
                        HashMap<String, Object> event = new HashMap<>();
                        event.put(EVENT_PHASE_KEY, PHASE_HIDDEN);
                        event.put(EVENT_TYPE_KEY, TYPE_BANNER);
                        dispatchLuaEvent(event);
                    }
                };

                // Run the activity on the uiThread
                coronaActivity.runOnUiThread(runnableActivity);
            }

            return 0;
        }
    }

    // [Lua] appodeal.getRewardParameters( [placementId] )
    private class GetRewardParameters implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "getRewardParameters";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.getRewardParameters( [placementId] )";

            if (!isSDKInitialized()) {
                return 0;
            }

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs > 1) {
                logMsg(ERROR_MSG, "Expected 0 or 1 argument, got " + nargs);
                return 0;
            }

            String placementId = null;

            if (!luaState.isNoneOrNil(1)) {
                if (luaState.type(1) == LuaType.STRING) {
                    placementId = luaState.toString(1);
                } else {
                    logMsg(ERROR_MSG, "placementId (string) expected, got: " + luaState.typeName(1));
                    return 0;
                }
            }

            // declare final vars for inner loop
            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
            final String fPlacementId = placementId;

            if (coronaActivity != null) {
                coronaActivity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Reward rewardParams;

                        if (fPlacementId == null) {
                            rewardParams = Appodeal.getReward();
                        } else {
                            rewardParams = Appodeal.getReward(fPlacementId);
                        }

                        if (rewardParams != null) {
                            // Create the event data (need to use Hashtable here for Corona's pushValue to work)
                            Map<String, Object> eventData = new Hashtable<>();
                            eventData.put(REWARD_AMOUNT_KEY, rewardParams.getAmount());
                            eventData.put(REWARD_NAME_KEY, rewardParams.getCurrency());

                            // Dispatch the Lua event
                            HashMap<String, Object> event = new HashMap<>();
                            event.put(EVENT_PHASE_KEY, PHASE_DATA_RECEIVED);
                            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
                            event.put(EVENT_DATA_KEY, eventData);
                            dispatchLuaEvent(event);
                        } else {
                            // Create the event data (need to use Hashtable here for Corona's pushValue to work)
                            Map<String, Object> eventData = new Hashtable<>();
                            eventData.put("ERROR", "Appodeal SDK wasn't initialized yet");

                            // Dispatch the Lua event
                            HashMap<String, Object> event = new HashMap<>();
                            event.put(EVENT_PHASE_KEY, PHASE_DATA_RECEIVED);
                            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
                            event.put(EVENT_DATA_KEY, eventData);
                            dispatchLuaEvent(event);
                        }
                    }
                });
            }

            return 0;
        }
    }

    // [Lua] appodeal.getVersion()
    private class GetVersion implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "getVersion";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.getVersion()";

            if (!isSDKInitialized()) {
                return 0;
            }

            // declare final vars for inner loop
            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();

            if (coronaActivity != null) {
                coronaActivity.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Log.i(CORONA_TAG, PLUGIN_NAME + ": " + PLUGIN_VERSION + " (SDK: " + PLUGIN_SDK_VERSION + ")");
                        // Dispatch the Lua event
                        HashMap<String, Object> event = new HashMap<>();
                        event.put("pluginVersion", PLUGIN_VERSION);
                        event.put("sdkVersion", PLUGIN_SDK_VERSION);
                        dispatchLuaEvent(event);
                    }
                });
            }
            luaState.pushString(Appodeal.getVersion());
            return 1;
        }
    }

    // [Lua] appodeal.load(adUnitType [, options ])
    @SuppressWarnings("UnusedAssignment")
    private class Load implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "load";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.load(adUnitType [, options ])";

            if (!isSDKInitialized()) {
                return 0;
            }

            // get number of arguments
            int nargs = luaState.getTop();
            if ((nargs < 1) || (nargs > 2)) {
                logMsg(ERROR_MSG, "Expected 1 or 2 arguments, got " + nargs);
                return 0;
            }

            String adUnitType = null;
            String placement = null;

            // Ensure the adUnitType is a string
            if (luaState.type(1) == LuaType.STRING) {
                adUnitType = luaState.toString(1);
            } else {
                logMsg(ERROR_MSG, "adUnitType (string) expected, got: " + luaState.typeName(1));
                return 0;
            }

            if (!luaState.isNoneOrNil(2)) {
                // check for options table
                if (luaState.type(2) == LuaType.TABLE) {
                    // traverse and verify all options
                    for (luaState.pushNil(); luaState.next(2); luaState.pop(1)) {
                        String key = luaState.toString(-2);

                        if (key.equals("placement")) {
                            if (luaState.type(-1) == LuaType.STRING) {
                                placement = luaState.toString(-1);
                            } else {
                                logMsg(ERROR_MSG, "options.placement (string) expected, got: " + luaState.typeName(-1));
                                return 0;
                            }
                        } else {
                            logMsg(ERROR_MSG, "Invalid option '" + key + "'");
                            return 0;
                        }
                    }
                }
                // no options table
                else {
                    logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(2));
                    return 0;
                }
            }

            ArrayList<String> disableAutoCacheAdTypes = (ArrayList<String>) appodealObjects.get(AUTOCACHE_KEY);
            if (!disableAutoCacheAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // validate ad unit type
            if (!validAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Invalid adUnitType '" + adUnitType + "'");
                return 0;
            }

            // make sure ad unit type was specified during init()
            ArrayList<String> supportedAdTypes = (ArrayList<String>) appodealObjects.get(SUPPORTED_ADTYPES_KEY);
            if (!supportedAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // declare final vars for inner loop
            final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
            final String fAdUnitType = adUnitType;
            final String fPlacement = placement;

            if (coronaActivity != null) {
                Runnable runnableActivity = new Runnable() {
                    public void run() {
                        int adType = NO_VALUE;

                        if (fAdUnitType.equals(TYPE_BANNER)) {
                            adType = Appodeal.BANNER;
                        } else if (fAdUnitType.equals(TYPE_INTERSTITIAL)) {
                            adType = Appodeal.INTERSTITIAL;
                        } else if (fAdUnitType.equals(TYPE_REWARDEDVIDEO)) {
                            adType = Appodeal.REWARDED_VIDEO;
                        }

                        if (fPlacement == null) {
                            Appodeal.cache(coronaActivity, adType);
                        } else {
                            // TODO: no placements available in the SDK yet for cache(). Add call when available.
                            Appodeal.cache(coronaActivity, adType);
                        }
                    }
                };

                coronaActivity.runOnUiThread(runnableActivity);
            }

            return 0;
        }
    }

    // [Lua] appodeal.isLoaded(adUnitType)
    private class IsLoaded implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "isLoaded";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState L) {
            functionSignature = "appodeal.isLoaded(adUnitType)";

            if (!isSDKInitialized()) {
                return 0;
            }

            // check number of args
            int numArgs = L.getTop();
            if (numArgs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got: " + numArgs);
                return 0;
            }

            String adUnitType = null;

            // Ensure the adUnitType is a string
            if (L.type(1) == LuaType.STRING) {
                adUnitType = L.toString(1);
            } else {
                logMsg(ERROR_MSG, "adUnitType (string) expected, got " + L.typeName(1));
                return 0;
            }

            // validate ad unit type
            if (!validAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Invalid adUnitType '" + adUnitType + "'");
                return 0;
            }

            // make sure ad unit type was specified during init()
            List<String> supportedAdTypes = (ArrayList<String>) appodealObjects.get(SUPPORTED_ADTYPES_KEY);
            if (!supportedAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // check if adUnitType is loaded
            int showStyle = NO_VALUE;

            if (adUnitType.equals(TYPE_BANNER)) {
                showStyle = Appodeal.BANNER_BOTTOM;
            } else if (adUnitType.equals(TYPE_INTERSTITIAL)) {
                showStyle = Appodeal.INTERSTITIAL;
            } else if (adUnitType.equals(TYPE_REWARDEDVIDEO)) {
                showStyle = Appodeal.REWARDED_VIDEO;
            }

            boolean isLoaded = false;

            if (showStyle != NO_VALUE) {
                isLoaded = Appodeal.isLoaded(showStyle);
            }

            L.pushBoolean(isLoaded);

            return 1;
        }
    }

    // [Lua] appodeal.canShow(adUnitType, placement)
    private class CanShow implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "canShow";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState L) {
            functionSignature = "appodeal.canShow(adUnitType, placement)";

            if (!isSDKInitialized()) {
                return 0;
            }

            // check number of args
            int numArgs = L.getTop();
            if ((numArgs < 1) || (numArgs > 2)) {
                logMsg(ERROR_MSG, "Expected 2 arguments, got: " + numArgs);
                return 0;
            }

            String adUnitType = null;
            String placement = null;

            // Ensure the adUnitType is a string
            if (L.type(1) == LuaType.STRING) {
                adUnitType = L.toString(1);
            } else {
                logMsg(ERROR_MSG, "adUnitType (string) expected, got " + L.typeName(1));
                return 0;
            }
            if (!L.isNoneOrNil(2)) {
                // Ensure the placement is a string
                if (L.type(2) == LuaType.STRING) {
                    placement = L.toString(2);
                } else {
                    logMsg(ERROR_MSG, "placement (string) expected, got " + L.typeName(2));
                    return 0;
                }
            }

            // validate ad unit type
            if (!validAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Invalid adUnitType '" + adUnitType + "'");
                return 0;
            }

            // make sure ad unit type was specified during init()
            List<String> supportedAdTypes = (ArrayList<String>) appodealObjects.get(SUPPORTED_ADTYPES_KEY);
            if (!supportedAdTypes.contains(adUnitType)) {
                logMsg(ERROR_MSG, "Request ignored. You didn't specify '" + adUnitType + "' in supportedAdTypes during init()");
                return 0;
            }

            // check if adUnitType is loaded
            int showStyle = NO_VALUE;

            if (adUnitType.equals(TYPE_BANNER)) {
                showStyle = Appodeal.BANNER_BOTTOM;
            } else if (adUnitType.equals(TYPE_INTERSTITIAL)) {
                showStyle = Appodeal.INTERSTITIAL;
            } else if (adUnitType.equals(TYPE_REWARDEDVIDEO)) {
                showStyle = Appodeal.REWARDED_VIDEO;
            }

            if (placement == null) {
                placement = "default";
            }

            boolean canShow = Appodeal.canShow(showStyle, placement);
            L.pushBoolean(canShow);

            return 1;
        }
    }

    // [Lua] appodeal.setSegmentFilter(options)
    private class SetSegmentFilter implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "setSegmentFilter";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.setSegmentFilter(options)";

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got " + nargs);
                return 0;
            }

            // params
            Hashtable<Object, Object> customRules = null;

            // check for options table (required)
            if (luaState.type(1) == LuaType.TABLE) {
                customRules = CoronaLua.toHashtable(luaState, 1);
            }
            // no options table
            else {
                logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(1));
                return 0;
            }

            // simple customRules key/value validation
            if (customRules != null) {
                for (Object objKey : customRules.keySet()) {
                    if (objKey instanceof Double) {
                        logMsg(ERROR_MSG, "options.customRules must be a key/value table");
                        return 0;
                    }
                }

                setRules(customRules);
            }

            return 0;
        }
    }

    // [Lua] appodeal.set728x90Banners(boolean)
    private class Set728x90Banners implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "set728x90Banners";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.set728x90Banners(boolean)";

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got " + nargs);
                return 0;
            }

            // check for boolean (required)
            if (luaState.type(-1) == LuaType.BOOLEAN) {
                boolean setBannersBool = luaState.toBoolean(-1);
                Appodeal.set728x90Banners(setBannersBool);
            }
            // no boolean
            else {
                logMsg(ERROR_MSG, "Boolean expected, got " + luaState.typeName(-1));
                return 0;
            }

            return 0;
        }
    }

    // [Lua] appodeal.trackInAppPurchase(options)
    private class TrackInAppPurchase implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "trackInAppPurchase";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.trackInAppPurchase(options)";

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got " + nargs);
                return 0;
            }

            // params
            double amount = NO_VALUE;
            String currency = null;

            // check for options table (required)
            if (luaState.type(1) == LuaType.TABLE) {
                // traverse and verify all options
                for (luaState.pushNil(); luaState.next(1); luaState.pop(1)) {
                    String key = luaState.toString(-2);

                    if (key.equals("amount")) {
                        if (luaState.type(-1) == LuaType.NUMBER) {
                            amount = luaState.toNumber(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.amount (number) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("currency")) {
                        if (luaState.type(-1) == LuaType.STRING) {
                            currency = luaState.toString(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.currency (string) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else {
                        logMsg(ERROR_MSG, "Invalid option '" + key + "'");
                        return 0;
                    }
                }
            }
            // no options table
            else {
                logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(1));
                return 0;
            }

            if (amount != NO_VALUE && currency != null) {
                final CoronaActivity coronaActivity = CoronaEnvironment.getCoronaActivity();
                Appodeal.trackInAppPurchase(coronaActivity, amount, currency);
            }

            return 0;
        }
    }

    // [Lua] appodeal.setUserDetails(options)
    private class SetUserDetails implements NamedJavaFunction {
        // Gets the name of the Lua function as it would appear in the Lua script
        @Override
        public String getName() {
            return "setUserDetails";
        }

        // This method is executed when the Lua function is called
        @Override
        public int invoke(LuaState luaState) {
            functionSignature = "appodeal.setUserDetails(options)";

            // get number of arguments
            int nargs = luaState.getTop();
            if (nargs != 1) {
                logMsg(ERROR_MSG, "Expected 1 argument, got " + nargs);
                return 0;
            }

            // params
            double age = NO_VALUE;
            String userId = null;
            String gender = null;

            // check for options table (required)
            if (luaState.type(1) == LuaType.TABLE) {
                // traverse and verify all options
                for (luaState.pushNil(); luaState.next(1); luaState.pop(1)) {
                    String key = luaState.toString(-2);

                    if (key.equals("age")) {
                        if (luaState.type(-1) == LuaType.NUMBER) {
                            age = luaState.toNumber(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.age (number) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("gender")) {
                        if (luaState.type(-1) == LuaType.STRING) {
                            gender = luaState.toString(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.gender (string) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else if (key.equals("userId")) {
                        if (luaState.type(-1) == LuaType.STRING) {
                            userId = luaState.toString(-1);
                        } else {
                            logMsg(ERROR_MSG, "options.userId (string) expected, got: " + luaState.typeName(-1));
                            return 0;
                        }
                    } else {
                        logMsg(ERROR_MSG, "Invalid option '" + key + "'");
                        return 0;
                    }
                }
            }
            // no options table
            else {
                logMsg(ERROR_MSG, "options table expected, got " + luaState.typeName(1));
                return 0;
            }

            // validate gender
            //            UserSettings.Gen appodealGender = null;
            //
            //            if (gender != null) {
            //                if (gender.equals(GENDER_FEMALE)) {
            //                    appodealGender = UserSettings.Gender.FEMALE;
            //                } else if (gender.equals(GENDER_MALE)) {
            //                    appodealGender = UserSettings.Gender.MALE;
            //                } else if (gender.equals(GENDER_OTHER)) {
            //                    appodealGender = UserSettings.Gender.OTHER;
            //                } else {
            //                    logMsg(ERROR_MSG, "'" + gender + "', invalid gender");
            //                    return 0;
            //                }
            //            }

            if (userId != null) {
                Appodeal.setUserId(userId);
            }

            if (age != NO_VALUE) {
                //Appodeal.setAge((int) age);
            }

            if (gender != null) {
                //Appodeal.setUserGender(appodealGender);
            }

            return 0;
        }
    }

    // -------------------------------------------------------------------
    // Delegates
    // -------------------------------------------------------------------

    // Banner delegates
    private class AppodealBannerDelegate implements BannerCallbacks {
        @Override
        public void onBannerExpired() {
        }

        @Override
        public void onBannerLoaded(int height, boolean isPrecache) {
            Hashtable<Object, Object> eventData = new Hashtable<>();
            eventData.put("height", height);
            eventData.put("isPrecache", isPrecache);

            // send Corona Lua event
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_LOADED);
            event.put(EVENT_TYPE_KEY, TYPE_BANNER);
            event.put(EVENT_DATA_KEY, eventData);
            dispatchLuaEvent(event);
        }

        @Override
        public void onBannerFailedToLoad() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_FAILED);
            event.put(EVENT_TYPE_KEY, TYPE_BANNER);
            event.put(CoronaLuaEvent.ISERROR_KEY, true);
            event.put(CoronaLuaEvent.RESPONSE_KEY, RESPONSE_LOADFAILED);
            dispatchLuaEvent(event);
        }

        @Override
        public void onBannerShown() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_DISPLAYED);
            event.put(EVENT_TYPE_KEY, TYPE_BANNER);
            dispatchLuaEvent(event);
        }

        @Override
        public void onBannerClicked() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_CLICKED);
            event.put(EVENT_TYPE_KEY, TYPE_BANNER);
            dispatchLuaEvent(event);
        }

        @Override
        public void onBannerShowFailed() {

        }
    }

    // -------------------------------------------------------------------
    // Interstitial delegates
    private class AppodealInterstitialDelegate implements InterstitialCallbacks {
        @Override
        public void onInterstitialExpired() {
        }

        @Override
        public void onInterstitialLoaded(boolean isPrecache) {
            Hashtable<Object, Object> eventData = new Hashtable<>();
            eventData.put("isPrecache", isPrecache);

            // send Corona Lua event
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_LOADED);
            event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
            event.put(EVENT_DATA_KEY, eventData);
            dispatchLuaEvent(event);
        }

        @Override
        public void onInterstitialFailedToLoad() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_FAILED);
            event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
            event.put(CoronaLuaEvent.ISERROR_KEY, true);
            event.put(CoronaLuaEvent.RESPONSE_KEY, RESPONSE_LOADFAILED);
            dispatchLuaEvent(event);
        }

        @Override
        public void onInterstitialShown() {
//      Map<String, Object> event = new HashMap<>();
//      event.put(EVENT_PHASE_KEY, PHASE_DISPLAYED);
//      event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
//      dispatchLuaEvent(event);
        }

        @Override
        public void onInterstitialClicked() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_CLICKED);
            event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
            dispatchLuaEvent(event);
        }

        @Override
        public void onInterstitialClosed() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_CLOSED);
            event.put(EVENT_TYPE_KEY, TYPE_INTERSTITIAL);
            dispatchLuaEvent(event);
        }

        @Override
        public void onInterstitialShowFailed() {

        }
    }

    // -------------------------------------------------------------------
    //  rewarded video delegates
    private class AppodealRewardedVideoDelegate implements RewardedVideoCallbacks {
        @Override
        public void onRewardedVideoExpired() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_EXPIRED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            event.put(CoronaLuaEvent.ISERROR_KEY, true);
            dispatchLuaEvent(event);

        }

        @Override
        public void onRewardedVideoClicked() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_CLICKED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            dispatchLuaEvent(event);

        }

        @Override
        public void onRewardedVideoLoaded(boolean loaded) {
            Hashtable<Object, Object> eventData = new Hashtable<>();
            eventData.put("loaded", loaded);

            // send Corona Lua event
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_LOADED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            event.put(EVENT_DATA_KEY, eventData);
            dispatchLuaEvent(event);
        }

        @Override
        public void onRewardedVideoFailedToLoad() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_FAILED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            event.put(CoronaLuaEvent.ISERROR_KEY, true);
            event.put(CoronaLuaEvent.RESPONSE_KEY, RESPONSE_LOADFAILED);
            dispatchLuaEvent(event);
        }

        @Override
        public void onRewardedVideoShown() {
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_SHOWN);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            dispatchLuaEvent(event);
        }

        @Override
        public void onRewardedVideoFinished(double rewardAmount, String rewardName) {
            // Create the event data (need to use Hashtable here for Corona's pushValue to work)
            Map<String, Object> eventData = new Hashtable<>();
            eventData.put(REWARD_AMOUNT_KEY, rewardAmount);
            eventData.put(REWARD_NAME_KEY, rewardName != null ? rewardName : "reward");

            // Send Corona Lua event
            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_PLAYBACK_ENDED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            event.put(EVENT_DATA_KEY, eventData);
            dispatchLuaEvent(event);
        }

        @Override
        public void onRewardedVideoClosed(boolean finished) {
            Hashtable<Object, Object> eventData = new Hashtable<>();
            eventData.put("finished", finished);

            Map<String, Object> event = new HashMap<>();
            event.put(EVENT_PHASE_KEY, PHASE_CLOSED);
            event.put(EVENT_TYPE_KEY, TYPE_REWARDEDVIDEO);
            event.put(EVENT_DATA_KEY, eventData);
            dispatchLuaEvent(event);
        }

        @Override
        public void onRewardedVideoShowFailed() {

        }
    }
}
