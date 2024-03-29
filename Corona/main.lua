-- Appodeal Plugin sample project

local appodeal = require( "plugin.appodeal" )
local widget = require( "widget" )
local json = require("json")

--------------------------------------------------------------------------
-- set up UI
--------------------------------------------------------------------------
display.setStatusBar( display.HiddenStatusBar )

-- forward declarations
local availableAdTypes = {"banner", "interstitial", "rewardedVideo"}
local currentAdType = 1
local platformName = system.getInfo("platformName")
local appKey = nil
local eventText = nil
local adTypeText = nil

if platformName == "Android" then
	if system.getInfo("targetAppStore") == "amazon" then
		appKey ="fee50c333ff3825fd6ad6d38cff78154de3025546d47a84f" -- com.appodeal.test
	else -- Google Play
		appKey = "fee50c333ff3825fd6ad6d38cff78154de3025546d47a84f" -- com.appodeal.test
	end
elseif platformName == "iPhone OS" then
	appKey = "68f7479070ea55f751054146a93b69ba50f839b2b8c577c4" -- com.appodeal.testing
end

local processEventTable = function(event)
    local logString = json.prettify(event):gsub("\\","")
    logString = "\nPHASE: ".. (event.phase or '-') .." - - - - - - - - - - - -\n" .. logString
    print(logString)
    return logString
end

local function toggleAdTypes()
	currentAdType = currentAdType + 1

	if currentAdType > #availableAdTypes then
		currentAdType = 1
	end

	adTypeText.text = "Current ad type: " .. availableAdTypes[currentAdType]
end

local function showAd()
	eventText.text = "Showing Ad..."

	-- Check if the ad is loaded before attempting to show
	if appodeal.isLoaded(availableAdTypes[currentAdType]) then
		appodeal.show(availableAdTypes[currentAdType])
	else
		eventText.text = availableAdTypes[currentAdType] .. " not loaded"
	end
end

-- Create the background
local background = display.newImageRect("back-whiteorange.png", display.actualContentWidth, display.actualContentHeight)
background.x = display.contentCenterX
background.y = display.contentCenterY

adTypeText = display.newText {
	text = "Current ad type: " .. availableAdTypes[currentAdType],
	font = native.systemFont,
	fontSize = 16,
	align = "left",
	width = 320,
	height = 20,
}
adTypeText.anchorX = 0
adTypeText.anchorY = 0
adTypeText.x = display.screenOriginX + 5
adTypeText.y = display.screenOriginY + 5
adTypeText:setFillColor(0)

eventText = display.newText {
	text = "",
	font = native.systemFont,
	fontSize = 12,
	align = "left",
	width = 310,
	height = 200,
}
eventText.anchorX = 0
eventText.anchorY = 0
eventText.x = display.screenOriginX + 5
eventText.y = display.contentCenterY
eventText:setFillColor(0)

local function appodealListener( event )
	eventText.text = processEventTable(event)
end

print("Using: ", appKey)

timer.performWithDelay( 1000, function() 
	appodeal.init(appodealListener, {
		disableWriteExternalPermissionCheck = true,
		appKey = appKey,
		-- testMode = true,
		bannerAnimation = true,
		hasUserConsent = true,
		customRules = {
			levels_played=5,
			boss_mode=true,
			user_level="beginner"
		}
	})
end)


-- Create a button
local button1 = widget.newButton(
{
	id = "changeAd",
	label = "Change Ad",
	width = 250,
	onRelease = function(event)
    --appodeal.getRewardParameters()
    toggleAdTypes()
    appodeal.canShow("banner")
	end,
})
button1.x = display.contentCenterX
button1.y = display.contentCenterY + 40

-- Create a button
local button2 = widget.newButton(
{
	id = "showAd",
	label = "Show Ad",
	onRelease = function(event)
		--appodeal.set728x90Banners(true)
		showAd()
		print("APPODEAL VERSION", appodeal.getVersion())
	end,
})
button2.x = display.contentCenterX
button2.y = display.contentCenterY + 90

local button3 = widget.newButton(
{
	id = "hide",
	label = "Hide Banner",
	onRelease = function(event)
		appodeal.hide("banner")
	end,
})
button3.x = display.contentCenterX
button3.y = display.contentCenterY + 130
