#!/bin/bash

set -e

pushd build &>/dev/null


while getopts p: flag
do
    case "${flag}" in
        p) 
            shift 2
            platform=${OPTARG}
            ;;
    esac
done

OPTION=$1

if [ "$OPTION" = 'help' ]
then
    echo build.sh - build debug library
    echo build.sh clean - clean the build
    echo build.sh release - build release library 
    echo build.sh release -p ios - build release ios library 
    exit
else
    build() {
        PREMAKE="premake5 gmake2 $1"
        eval $PREMAKE
        if [ "$OPTION" = "clean" ]
        then
            make clean
            make clean config=release
        elif [ "$OPTION" = "release" ]
        then
            make config=release -j7
        else
            make -j7
        fi
    }

    case $platform in 
        ios)
            echo "Building for iOS"
            export IOS_SYSROOT=$(xcrun --sdk iphoneos --show-sdk-path)
            build "--os=ios"
            build "--os=ios --variant=emulator"
            if [ "$OPTION" = "clean" ]
            then
                exit
            elif [ "$OPTION" = "release" ]
            then
                config="release"
            else
                config="debug"
            fi
            xcrun -sdk iphoneos lipo -create -arch x86_64 ios_sim/bin/$config/librive.a ios/bin/$config/librive.a -output ios/bin/$config/librive_fat.a
            # print all the available architectures
            lipo -info ios/bin/$config/librive_fat.a
        ;;
        *)
            build
        ;;
    esac
fi

popd &>/dev/null
