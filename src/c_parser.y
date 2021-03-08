%code requires{
//  #include "c_lexparse.hpp"
  #include "../include/ast.hpp"
  #include <cassert>


  extern const TranslationalUnit *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}
%union{
  const TranslationalUnit* tu;
  int number;
  std::string *string;
  char _char;
}

%token IDENTIFIER INTCONST
%token INT
%token RETURN

%type <tu> ROOT TranslationalUnit FunctionDef JumpStatement TypeSpecifier PrimaryExpr
%type <string> IDENTIFIER INTCONST
//%type <_char> Operator

%start ROOT
%%

ROOT: TranslationalUnit {g_root = $1;}


TranslationalUnit: FunctionDef {$$ = $1;}

FunctionDef: TypeSpecifier IDENTIFIER '(' ')' '{' JumpStatement '}' {$$ = new FunctionDef($1,$2,$6);}

JumpStatement: RETURN PrimaryExpr ';' {$$ = new JumpStat("return",$2);}
              |RETURN ';' {$$ = new JumpStat("return");}


TypeSpecifier: INT {$$ = new TypeSpec("int");}


PrimaryExpr: INTCONST {$$=new PrimaryExpr("int",$1);}
             |IDENTIFIER {$$ = new PrimaryExpr("identif",$1);/*}


Operator: '&'	{ $$ = '&'; }
        | '*'	{ $$ = '*'; }
        | '+'	{ $$ = '+'; }
        | '-'	{ $$ = '-'; }
        | '~'	{ $$ = '~'; }
      | '!'	{ $$ = '!'; */}



%%

const TranslationalUnit* g_root; // Definition of variable (to match declaration earlier)

const TranslationalUnit *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
