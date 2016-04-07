#!/bin/bash

#This script is supposed to be in the "scripts" directory
#Go back to parent directory
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
cd ..

#Activate "emscripten"
EMSCRDIR="EmscriptenSDK"

"./$EMSCRDIR/emsdk" activate latest

# source Emscripten
source "$EMSCRDIR/emsdk_env.sh"

#Make temporary dir
directory=/tmp/$RANDOM-$$-emscripten
mkdir $directory

echo "TEMPORARY DIRECTORY: $directory"

# copy source in /tmp/<random-dir>
cp -r "source/" "$directory"
# copy assets in /tmp/<random-dir>
cp -r "assets" "$directory"

#cd to tmp dir
cd "$directory"

# generate makefile from original makefile
EMSCRIPTEN_MAKE_ARGS_AUTO=$(< "$directory/makefile_em")
echo $EMSCRIPTEN_MAKE_ARGS_AUTO
mv makefile makefile.original
perl -pe 's/\#\<EMSCRIPTEN_FLAGS\>/`cat makefile_em`/e' makefile.original > makefile

#Run emmake
emmake make

#Copy "executable file" to 
#remove old executable:
PROJECTDIR="$(dirname "$DIR")"
#rm -fr "$PROJECTDIR/build_web" &
mkdir -p "$PROJECTDIR/build_web" 
mv {Game.html,Game.js,Game.data} "$PROJECTDIR/build_web/" && echo -e "\x1B[32mSuccess! The compiled files should be at build_web/\x1B[0m"

exit

#remove temporary directory
rm -fr "$directory"

