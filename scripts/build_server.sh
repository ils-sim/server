#/bin/bash
set -ex

function cmake_build {
	mkdir -p build
	cd build
	cmake -G "Unix Makefiles" ..
	make -j`grep -c ^processor /proc/cpuinfo`
	cd ..
}

cd common/protocol
./build.sh

cd ../..
cmake_build
