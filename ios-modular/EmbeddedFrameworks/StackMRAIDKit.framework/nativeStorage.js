(function() {
    var nativeStorage = window.nativeStorage = {};
    
    var EVENTS = nativeStorage.EVENTS = {
        "READ_FILE_SUCCESS_EVENT" :       "readFileSuccess",
        "READ_DEFAULTS_SUCCESS_EVENT" :   "readDefaultsSuccess",
        "ERROR_EVENT" :                   "error",
    };
    
    var listeners = {};
    
    /// JS API
    nativeStorage.addEventListener = function(event, listener) {
        if (!event || !listener || !contains(event, EVENTS)) {
            return;
        }
        var listenersForEvent = listeners[event] = listeners[event] || [];
        // Check to make sure that the listener isn't already registered
        for (var i = 0; i < listenersForEvent.length; i++) {
            var str1 = String(listener);
            var str2 = String(listenersForEvent[i]);
            if (listener === listenersForEvent[i] || str1 === str2) {
                return;
            }
        }

        listenersForEvent.push(listener);
    };
    
    nativeStorage.removeEventListener = function(event, listener) {
        if (!event || !contains(event, EVENTS)) {
            return;
        }
        
        if (listeners.hasOwnProperty(event)) {
            if (listener) {
                var listenersForEvent = listeners[event];
                // try to find the given listener
                var len = listenersForEvent.length;
                for (var i = 0; i < len; i++) {
                    var registeredListener = listenersForEvent[i];
                    var str1 = String(listener);
                    var str2 = String(registeredListener);
                    if (listener === registeredListener || str1 === str2) {
                        listenersForEvent.splice(i, 1);
                        break;
                    }
                }
                if (listenersForEvent.length === 0) {
                    delete listeners[event];
                }
            } else {
                delete listeners[event];
            }
        }
    };
    
    nativeStorage.readFile = function(encodedPath) {
        var params = "path=" + encodeURIComponent(encodedPath);
        callNative("readFile?" + params);
    }
    
    nativeStorage.writeFile = function(encodedPath, encodedData) {
        var params =
        "path=" + encodeURIComponent(encodedPath) +
        "&data=" + encodeURIComponent(encodedData);
        callNative("writeFile?" + params);
    }
    
    nativeStorage.readDefaults = function(encodedPath) {
        var params = "path=" + encodeURIComponent(encodedPath);
        callNative("readDefaults?" + params);
    }
    
    nativeStorage.writeDefaults = function(encodedPath, encodedData) {
        var params =
        "path=" + encodeURIComponent(encodedPath) +
        "&data=" + encodeURIComponent(encodedData);
        callNative("writeDefaults?" + params);
    }
    
    /// SDK API
    nativeStorage.fireReadFileSuccessEvent = function(path, data) {
        fireEvent(nativeStorage.EVENTS.READ_FILE_SUCCESS_EVENT, path, data);
    };
    
    nativeStorage.fireReadDefaultsSuccessEvent = function(path, data) {
        fireEvent(nativeStorage.EVENTS.READ_DEFAULTS_SUCCESS_EVENT, path, data);
    };
    
    nativeStorage.fireErrorEvent = function(message) {
        fireEvent(nativeStorage.EVENTS.ERROR_EVENT, message);
    };
    
    /// Helpers
    var contains = function(value, array) {
        for (var i in array) {
            if (array[i] === value) {
                return true;
            }
        }
        return false;
    };
    
    var callNative = function(command) {
        window.webkit.messageHandlers.nativeStorage.postMessage(command);
    }
    
    var fireEvent = function(event) {
        var args = Array.prototype.slice.call(arguments);
        args.shift();
        var tempEventListeners = listeners[event];
        if (tempEventListeners) {
            var eventListeners = tempEventListeners.slice();
            var len = eventListeners.length;
            for (var i = 0; i < len; i++) {
                eventListeners[i].apply(null, args);
            }
        }
    };
}());
