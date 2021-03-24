#!/usr/bin/env bash

rm -rf working

selection=$1

echo "Making c_compiler"
make bin/c_compiler

mkdir working

find compiler_tests/"$selection" -type f -not -iname "*_driver.c"|while read -r testcase; do
    echo "Compiling $testcase in $selection"
    test_case_bn=$(basename "$testcase" .c)
    echo "$test_case_bn"
    bin/c_compiler -S "$testcase" > working/"$test_case_bn".s
    echo "compiled $test_case_bn"
    mips-linux-gnu-gcc -mfp32 < working/"$test_case_bn".s > working/"$test_case_bn".o 
    mips-linux-gnu-gcc -mfp32 -static < working/"$test_case_bn".o compiler_tests/"$selection"/"$test_case_bn"_driver.c > working/"$test_case_bn"
    qemu-mips working/"$test_case_bn"
    exit=$?
    if [ $exit -eq 0 ]; then 
        echo "PASS"
    else
        echo "FAIL"
    fi
done
