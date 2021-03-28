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
    bin/c_compiler -S "$testcase" -o working/"$test_case_bn".s
    mips-linux-gnu-gcc -mfp32 -o working/"$test_case_bn".o -c working/"$test_case_bn".s 
    mips-linux-gnu-gcc -mfp32 -static -o working/"$test_case_bn" working/"$test_case_bn".o compiler_tests/"$selection"/"$test_case_bn"_driver.c 
    qemu-mips working/"$test_case_bn"
    exit=$?
    if [ $exit -eq 0 ]; then 
        echo "PASS"
    else
        echo "FAIL"
    fi
done
