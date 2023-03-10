CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

# bin/c_compiler : bin/compiler src/wrapper.sh
# 	cp src/wrapper.sh bin/c_compiler
# 	chmod u+x bin/c_compiler

bin/c_compiler : src/compiler.cpp src/c_lexer.yy.cpp src/c_parser.tab.cpp src/c_parser.tab.hpp include/*
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^
	chmod u+x bin/c_compiler
	dos2unix ./run_tests.sh

bin/toMIPS: src/c_lexer.yy.cpp src/c_parser.tab.cpp src/c_parser.tab.hpp include/*
	make src/c_parser.tab.cpp src/c_parser.tab.hpp src/c_lexer.yy.cpp
	g++ $(CPPFLAGS) src/test_toMIPS.cpp -o bin/toMIPS $^

bin/pretty_print: src/c_lexer.yy.cpp src/c_parser.tab.cpp src/c_parser.tab.hpp include/*
	make src/c_parser.tab.cpp src/c_parser.tab.hpp src/c_lexer.yy.cpp
	g++ $(CPPFLAGS) src/test_parser.cpp -o bin/pretty_print $^

src/c_parser.tab.cpp src/c_parser.tab.hpp: src/c_parser.y
	bison -v -d src/c_parser.y -o src/c_parser.tab.cpp

src/c_lexer.yy.cpp: src/c_lexer.flex src/c_parser.tab.hpp
	flex -o src/c_lexer.yy.cpp src/c_lexer.flex


clean :
	rm -f src/*.tab.cpp
	rm -f src/*.yy.cpp
	rm -f working/*.c
	rm -f working/*.txt
	rm -f working/*/*.c
	rm -f src/c_parser.tab.hpp.gch
	rm -f src/*.output
