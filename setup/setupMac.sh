#!/bin/bash

echo "Setting up Gaming Engine Runtime Environment"
foundroot=false
if [ "$EUID" -ne "0" ] ; then
    echo -e "\x1B[31mYou must run this script as root!\x1B[0m"
    echo -e "\x1B[31mPlease enter your Password!\x1B[0m"
    echo 
    sudo bash $0 && foundroot=true
else
	echo -e "\x1B[34mRunning script with root privilleges.\x1B[0m"
	foundroot=true
fi

if [ "$foundroot" = false ]; then
	echo -e "\x1B[31mSorry, cannot continue. Run this script as root!\x1B[0m"
	exit 1
elif [  "$(id -u)" != "0" ]; then
	exit 0
fi

echo "Copying Frameworks"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
sudo cp -R $DIR/files_mac/*.framework /Library/Frameworks/ 2>/dev/null 1>/dev/null 

echo -e "\x1B[32mDone! You should now be able to run the game from build/Game\x1B[0m"




