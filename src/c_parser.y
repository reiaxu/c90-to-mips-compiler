%code requires{
  #include "c_lexparse.hpp"
  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}
%token IDENTIFIER INTCONST

%token INT

%token RETURN

%start Function
%%
TranslationalUnit:
              FunctionDef {}
              ;
FunctionDef:
              TypeSpecifier IDENTIFIER '(' ')' '{' JumpStatement '}' {}
              ;
JumpStatement:
              RETURN PrimaryExpr ';' {}
              |RETURN ';' {}
              ;

TypeSpecifier:
              INT {}
              ;

PrimaryExpr:
          INTCONST {$$=$1;}
          |IDENTIFIER {$$ = $1}
		      ;

Operator:
          '&'	{ $$ = '&'; }
        | '*'	{ $$ = '*'; }
        | '+'	{ $$ = '+'; }
        | '-'	{ $$ = '-'; }
        | '~'	{ $$ = '~'; }
        | '!'	{ $$ = '!'; }
        ;


%%
