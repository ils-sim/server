#/bin/bash
set -ex

if [ ! -d "$HOME/cppcheck" ]; then
	wget https://github.com/danmar/cppcheck/archive/1.75.zip
	unzip 1.75.zip
	cd cppcheck-1.75/
	make PREFIX=$HOME/cppcheck SRCDIR=build CFGDIR=cfg HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"
	make install
else
  echo "Using cached directory."
fi
