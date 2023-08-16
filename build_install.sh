#!/bin/bash

if [ -e "/usr/share/fonts/adobe-source-code-pro/" ] ; then
    echo "-- Source Code Pro font are installed."
else
    read -p ">> Install font for project? [n/Y] " font
    if [ "$font" = "Y" ] || [ "$font" = "y" ] ; then
        printf "-- Installing font... ."
        sudo cp -n -r ./resources/adobe-source-code-pro/ /usr/share/fonts > /dev/null
        printf "Done\n"

        printf "-- Refresh fonts... ."
        sudo fc-cache -fv > /dev/null
        printf "Done\n"
    fi
fi

read -p ">> Build project? [n/Y] " build
if [ "$build" = "Y" ] || [ "$build" = "y" ] ; then
    mkdir -p build
    cd build

    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

    read -p ">> Install project? [n/Y] " install
    if [ "$install" = "Y" ] || [ "$install" = "y" ] ; then
        sudo make install
    fi
fi
