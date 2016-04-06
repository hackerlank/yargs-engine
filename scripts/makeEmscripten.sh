#!/bin/bash

#This script is supposed to be in the "scripts" directory
#Go back to parent directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
cd ..

#Activate "emscripten"
./
# source Emscripten

#Make temporary dir
directory=/tmp/$RANDOM-$$-emscripten
mkdir $directory

# copy source in /tmp/<random-dir>
cp -r "source/" "$directory"
# copy assets in /tmp/<random-dir>
cp -r "assets/" "$directory"

# generate makefile from original makefile
	# include all assets
# cd /tmp/<random-dir>
# emmake 
# copy compiled files back
# delete tmp?


