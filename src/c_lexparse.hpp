#ifndef c_lexparse_hpp
#define c_lexparse_hpp

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

#endif
