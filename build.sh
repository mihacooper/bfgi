#!/bin/bash

############################################
# enviroment variables
############################################

export DEBUG_MODE=0 

for par in $@
do
	if [ $par == "debug" ]; then
		DEBUG_MODE=1
	fi
done

export BIN_DIRECTORY=${PWD}/bin
export LIBRARY_DIRECTORY=${PWD}/lib
export BUILD_DIRECTORY=${PWD}/build

export PREF_FLAG="-O2"
if [ $DEBUG_MODE -eq 1 ]; then
	PREF_FLAG="-g -O0"
fi
export CXX_FLAGS="$PREF_FLAG -fPIC -Wno-unused-but-set-variable -Wno-unused-variable -Wno-write-strings -std=c++11 -Wno-literal-suffix"
export C_FLAGS="$PREF_FLAG -fPIC -Wno-unused-but-set-variable -Wno-unused-variable -Wno-write-strings" #-std=c99

############################################
# cmake
############################################

export CMAKE_FLAGS=""

if [ ! -d $BIN_DIRECTORY ]; then
	mkdir $BIN_DIRECTORY
fi

if [ ! -d $BUILD_DIRECTORY ]; then
	mkdir $BUILD_DIRECTORY
fi

cd $BUILD_DIRECTORY;

cmake $CMAKE_FLAGS ../

############################################
# make
############################################

make -j4
