#/bin/bash
set -e

cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --xml --xml-version=2 Einsatz Fahrzeug Sync com \
-ibuild \
-icom/build \
-icom/test/com_convert_test \
-Icom/src \
-Iprotocol/cpp_out --inline-suppr 2> cppcheck-result.xml
