#/bin/bash
set -ex

cd common
./scripts/clean_server.sh
cd ..

rm -rf build
