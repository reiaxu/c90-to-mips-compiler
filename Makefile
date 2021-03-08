CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

bin/pretty_print: src/c_lexer.yy.cpp src/c_parser.tab.cpp src/test_parser.cpp include/*
	g++ $(CPPFLAGS) -o bin/pretty_print $^

src/c_parser.tab.cpp src/c_parser.tab.hpp: src/c_parser.y
	bison -v -d src/c_parser.y -o src/c_parser.tab.cpp

src/c_lexer.yy.cpp: src/c_lexer.flex src/c_parser.tab.hpp
	flex -o src/c_lexer.yy.cpp src/c_lexer.flex


clean :
	rm src/*.tab.cpp
	rm src/*.yy.cpp
