#/bin/bash
set -ex

if [ ! -e "$HOME/cppcheck/cppcheck" ]; then
	wget https://github.com/danmar/cppcheck/archive/1.75.zip
	unzip 1.75.zip
	cd cppcheck-1.75/
	make PREFIX=$HOME/cppcheck SRCDIR=build CFGDIR=cfg HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"
	make install PREFIX=$HOME/cppcheck CFGDIR=$HOME/cppcheck/bin/cfg
else
  echo "Using cached directory."
fi
