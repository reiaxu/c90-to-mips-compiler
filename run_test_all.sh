#!/usr/bin/env bash

rm -rf working

# selection=$1

echo "Making c_compiler"
make bin/c_compiler

mkdir working

PASSED=0
CHECKED=0

allPASSED=()
allFAILED=()

for CATEGORY in compiler_tests/* ; do
    SECTION=$(basename $CATEGORY)
    mkdir -p working/$SECTION

    for DRIVER in compiler_tests/$SECTION/*_driver.c ; do
        CHECKED=$(( CHECKED+1 ))
        NAME=$(basename $DRIVER _driver.c)
        TESTCODE=compiler_tests/$SECTION/$NAME.c

        printf "Test case %-15s :\t" $SECTION"/"$NAME


        bin/c_compiler -S compiler_tests/$SECTION/$NAME.c -o working/${SECTION}/${NAME}.s
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Couldn't output to .s\n"
            allFAILED+=( $NAME )
            continue
        fi

        mips-linux-gnu-gcc -mfp32 -o working/${SECTION}/${NAME}.o -c working/${SECTION}/${NAME}.s
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Couldn't compile driver program using GCC.\n"
            allFAILED+=( $NAME )
            continue
        fi

        mips-linux-gnu-gcc -mfp32 -static -o working/${SECTION}/${NAME} working/${SECTION}/${NAME}.o compiler_tests/${SECTION}/${NAME}_driver.c
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Linker returned error message.\n"
            allFAILED+=( $NAME )
            continue
        fi

        qemu-mips working/${SECTION}/${NAME}
        RESULT=$?
        if [[ "$RESULT" -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Testcase returned $RESULT, but expected 0.\n"
            allFAILED+=( $NAME )
            continue
        fi

        printf "\e[1;32mPass\e[0m\n"
        PASSED=$(( PASSED+1 ))
        allPASSED+=( $NAME )
    done
done

echo "########################################"
echo " Passed ${PASSED} out of ${CHECKED}"
echo ""
echo "PASSED: ${allPASSED[@]}	 "
echo "########################################"
echo "FAILED: ${allFAILED[@]} "
