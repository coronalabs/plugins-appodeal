local metadata =
{
	plugin =
	{
		format = 'staticLibrary',
		staticLibs = { 'plugin_appodeal_base', "xml2", "z", },
		frameworks = {"JavaScriptCore", "CoreBluetooth", "WebKit", "CoreTelephony", "StackFoundation", "StackMRAIDKit", "StackNASTKit", "StackRichMedia", "StackUIKit", "StackVASTAssets", "StackVASTKit", "StackVideoPlayer", "StackXML", "Appodeal", "Protobuf", "StackCrashReporter"},
		frameworksOptional = {"SafariServices", "AdSupport", "AppTrackingTransparency"},
		usesSwift  = true,
	},
}

return metadata
