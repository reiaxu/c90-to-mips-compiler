%code requires{
//  #include "c_lexparse.hpp"
  #include "../include/ast.hpp"
  #include <cassert>
  #include <string>



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

%type <tu> ROOT TranslationalUnit FunctionDef CompoundStatement StatementList Statement JumpStatement DeclarationSpecifier TypeSpecifier PrimaryExpr
%type <string> IDENTIFIER INTCONST Declarator DirectDeclarator
//%type <_char> Operator

%start ROOT
%%

ROOT: TranslationalUnit {g_root = $1;}

TranslationalUnit: FunctionDef {$$ = $1;}

FunctionDef: DeclarationSpecifier Declarator CompoundStatement {$$ = new FunctionDef($1, $2, $3);}

CompoundStatement: '{' '}' {}
                | '{' StatementList '}' {$$=$2;}

StatementList: Statement {$$=$1;}

Statement: JumpStatement {$$=$1;}

JumpStatement: RETURN PrimaryExpr ';' {$$ = new JumpStat("return",$2);}
              |RETURN ';' {$$ = new JumpStat("return");}

DeclarationSpecifier: TypeSpecifier {$$ = $1;}

Declarator: DirectDeclarator {$$=$1;}

DirectDeclarator: IDENTIFIER {$$ = $1;}
                | DirectDeclarator '(' ')' {$$=$1;}

TypeSpecifier: INT {$$ =new TypeSpec("int");}

PrimaryExpr: INTCONST {$$=new PrimaryExpr("int", $1);}
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
