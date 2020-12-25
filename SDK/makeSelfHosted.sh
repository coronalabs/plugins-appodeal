#!/bin/bash -e
set -e

REV="2100.9999"
PLUGIN_DIR=plugins


DST_DIR="$HOME/Solar2DPlugins/com.coronalabs/"
rm -rf "$DST_DIR"
mkdir -p "$DST_DIR"

(
	cd "$(dirname "$0")/$PLUGIN_DIR"
	for pluginName in *
	do
		REV=
		if [ -d "$pluginName/plugins" ]
		then
			REV=$(cd "$pluginName/plugins"; find . -maxdepth 1 -execdir echo {} \; | sort | tail -1)
		fi
		if [ "$REV" ] && [ -d "$pluginName/plugins/$REV" ]
		then
			(
				cd "$pluginName/plugins/$REV"
				for platform in *
				do
					if [ "$platform" == "universal" ]
					then
						continue
					fi
					(
						cd "$platform"
						tarPath="$DST_DIR/plugin.appodeal.$pluginName/$platform"
						mkdir -p "$tarPath"
						COPYFILE_DISABLE=1 tar -czvf "$tarPath/data.tgz" -- * &> "$tarPath/$REV.txt"
					)
				done
			)
		fi
	done
)