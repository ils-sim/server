#/bin/bash
set -e

cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive Einsatz Fahrzeug Sync com \
-ibuild \
-icom/build \
-icom/test/com_convert_test \
-Icom/src \
-Iprotocol/cpp_out --inline-suppr
