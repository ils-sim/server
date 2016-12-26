#/bin/bash
set -ex

cppcheck --version

cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive Einsatz Fahrzeug Sync \
-ibuild \
-icommon/build \
-icommon/test/com_convert_test \
-Icommon/src \
-Icommon/protocol/cpp_out --inline-suppr 2> cppcheck-result.txt

if [ ! -s cppcheck-result.txt ]
    then
        exit 0
    fi

    cat cppcheck-result.txt
    exit 1
fi

