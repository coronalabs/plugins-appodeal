#!/bin/bash -e

SRC="$(cd $(dirname $0); pwd)"
OUTPUT_DIR="$SRC/build"
# xcodebuild -configuration Release clean
xcodebuild build -derivedDataPath "${OUTPUT_DIR}" -workspace iOSPods.xcworkspace -configuration Release -scheme iOSPods -sdk iphonesimulator
xcodebuild build -derivedDataPath "${OUTPUT_DIR}" -workspace iOSPods.xcworkspace -configuration Release -scheme iOSPods -sdk iphoneos

