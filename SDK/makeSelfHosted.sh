#!/bin/bash -e
set -e

PLUGIN_DIR=plugins


(
	cd "$(dirname "$0")/$PLUGIN_DIR"
	for pluginName in *
	do
		if [ -d "$pluginName/plugins" ]
		then
			(
				cd "$pluginName/plugins"
				s2deploy
			)
		fi
	done
)
echo Done