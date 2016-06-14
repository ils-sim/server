#/bin/bash

LD_LIBRARY_PATH="/usr/local/lib"

set -e

function cmake_build {
	mkdir -p build
	cd build
	cmake -G "Unix Makefiles" ..
	make
	cd ..
}

cd protocol
./build.sh

cd ../com
cmake_build

cd ..
cmake_build
