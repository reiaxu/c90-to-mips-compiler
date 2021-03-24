#!/bin/bash

if [[ "$1" -eq 0 ]]; then 
    COMPILER=bin/c_compiler
elif [[ "$1" -eq 1 ]]; then
    COMPILER=bin/c_compiler
    make clean
    make -B ${COMPILER}
elif [[ "$1" -eq 2 ]]; then
    COMPILER=c_compiler_ref.sh
fi

echo ""
echo "========================================"
echo " Testing compiler : ${COMPILER}"
echo ""

PASSED=0
CHECKED=0


for CATEGORY in compiler_tests/* ; do
    SECTION=$(basename $CATEGORY)
    mkdir -p working/$SECTION
    
    for DRIVER in compiler_tests/$SECTION/*_driver.c ; do
        CHECKED=$(( CHECKED+1 ))
        NAME=$(basename $DRIVER _driver.c)
        TESTCODE=compiler_tests/$SECTION/$NAME.c

        printf "Test case %-15s :\t" $NAME  

        # Compile driver with normal GCC
        mips-linux-gnu-gcc -c $DRIVER -o working/${SECTION}/${NAME}_driver.o 2> working/${SECTION}/${NAME}_driver.compile.stderr
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Couldn't compile driver program using GCC.\n"
            continue
        fi  

        # Compile test function with compiler under test to assembly
        cat $TESTCODE | $COMPILER > working/$SECTION/$NAME.s  2> working/${SECTION}/${NAME}.compile.stderr
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Compiler returned error message.\n"
            continue
        fi    

        # Link driver object and assembly into executable
        mips-linux-gnu-gcc -static working/${SECTION}/${NAME}.s working/${SECTION}/${NAME}_driver.o -o working/${SECTION}/${NAME}.elf 2> working/${SECTION}/${NAME}.link.stderr
        if [[ $? -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Linker returned error message.\n"
            continue
        fi

        # Run the actual executable
        qemu-mips working/${SECTION}/${NAME}.elf > working/$SECTION/$NAME.elf.stdout
        RESULT=$?
        if [[ "$RESULT" -ne 0 ]]; then
            printf "\e[1;31mError\e[0m : Testcase returned $RESULT, but expected 0.\n"
            continue
        fi

        printf "\e[1;32mPass\e[0m\n"
        PASSED=$(( PASSED+1 ))
    done
done

echo "########################################"
echo " Passed ${PASSED} out of ${CHECKED}"
echo ""