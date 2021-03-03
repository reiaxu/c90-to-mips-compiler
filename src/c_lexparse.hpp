#ifndef c_lexparse_hpp
#define c_lexparse_hpp

#include<string>

extern int yylex();

enum TokenType{
//Chars are already enumerated via ASCII
//note that extended ASCII is up to 255
  IDENTIFIER = 256,
//literals
  INTCONST = 257,
//types
  INT = 258,
//keywords
  RETURN = 259,
};

union TokenVal{
    int num;
    std::string *str;
};

extern TokenVal yylval;

#endif
