#!/bin/bash
set -e
echo "-----Compiling lexer-----"
flex -o c_lexer.yy.cpp c_lexer.flex
echo "-----Compiling test source files-----"
g++ test_lexer.cpp  c_lexer.yy.cpp c_lexparse.hpp
echo "-----Running Program-----"
./a.out
