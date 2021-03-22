#!/bin/bash

mkdir -p working/integer

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    # This works on a GNU version of sed. I think this
    # will work in OSX as well, but don't have a machine
    # on which to test that. From reading the OSX docs,
    # it looks compatible.
    # The code \x0D is the ASCII code of carriage-return,
    # so it the regex should delete any CRs at the end of
    # a line (or anywhere in a line)
    DOS2UNIX="cat"
    # Tested for combinations of:
    # - Ubuntu
    # - Cygwin
    # and inputs formats:
    # - LF
    # - CRLF
fi

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean

echo "========================================"
echo " Force building prettyprint"
make -B bin/pretty_print
if [[ "$?" -ne "0" ]]; then
    echo "Error while building prettyprint."
    exit 1;
fi

echo "========================================="

PASSED=0
CHECKED=0

for i in compiler_tests/integer/*; do
    b=$(basename ${i});


    echo "==========================="
    echo ""
    echo "Input file : ${i}"
    echo "Testing $b"

    bin/pretty_print \
        < $i \
        > working/integer/$b

    OK=0;    
    GOT_OUTPUT=$(echo $(cat working/integer/$b | ${DOS2UNIX} ))
    REF_OUTPUT=$(echo $(cat $i | ${DOS2UNIX} ))

    if [[ "${GOT_OUTPUT}" != "${REF_OUTPUT}" ]]; then
        echo "  got output : ${GOT_OUTPUT}"
        echo "  ref output : ${REF_OUTPUT}"
        echo "  FAIL!";
        OK=1;
    fi

    if [[ "$OK" -eq "0" ]]; then
        PASSED=$(( ${PASSED}+1 ));
    fi

    CHECKED=$(( ${CHECKED}+1 ));

    echo ""
    
done

echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo ""

RELEASE=$(lsb_release -d)
if [[ $? -ne 0 ]]; then
    echo ""
    echo "Warning: This appears not to be a Linux environment"
    echo "         Make sure you do a final run on a lab machine or an Ubuntu VM"
else
    grep -q "Ubuntu 16.04" <(echo $RELEASE)
    FOUND=$?

    if [[ $FOUND -ne 0 ]]; then
        echo ""
        echo "Warning: This appears not to be the target environment"
        echo "         Make sure you do a final run on a lab machine or an Ubuntu VM"
    fi
fi
