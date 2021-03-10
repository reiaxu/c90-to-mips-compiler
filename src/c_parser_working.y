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
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOID
%token STRUCT ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

// %type <tu> parameter_declaration primary_expression postfix_expression argument_expression_list unary_expression multiplicative_expression additive_expression shift_expression
// %type <tu> relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
// %type <tu> parameter_list conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers init_declarator_list init_declarator
// %type <tu> parameter_type_list  storage_class_specifier type_specifier  declarator direct_declarator initializer initializer_list labeled_statement compound_statement declaration_list statement_list expression_statement selection_statement iteration_statement jump_statement statement translation_unit function_definition
// %type <string> IDENTIFIER CONSTANT STRING_LITERAL
// %type <number> unary_operator pointer
// %type <en_ass> assignment_operator
// %type <tu> abstract_declarator direct_abstract_declarator specifier_qualifier_list type_name

%type <tu> ROOT TranslationalUnit FunctionDef CompoundStatement StatementList Statement JumpStatement DeclarationSpecifier TypeSpecifier
%type <tu> PostfixExpr UnaryExpr PrimaryExpr 
%type <string> Declarator DirectDeclarator
%type <string> IDENTIFIER CONSTANT

%type <_char> UnaryOp

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

MultiplicativeExpr: UnaryExpr {}
                	| MultiplicativeExpr '*' UnaryExpr {}
                	| MultiplicativeExpr '/' UnaryExpr {}
                	| MultiplicativeExpr '%' UnaryExpr {}
                	;

UnaryExpr: PostfixExpr {$$=$1;}
        	| INC_OP UnaryExpr {;}
        	| DEC_OP UnaryExpr {;}
        	| UnaryOp UnaryExpr {;}
        	| SIZEOF UnaryExpr {;}
//        	| SIZEOF '(' type_name ')' {;}
        	;

PostfixExpr: PrimaryExpr {$$=$1;}
//          	| PostfixExpr '[' expression ']' {;}
          	| PostfixExpr '(' ')' {;}
//          	| PostfixExpr '(' argument_expression_list ')' {;}
          	| PostfixExpr '.' IDENTIFIER {;}
          	| PostfixExpr PTR_OP IDENTIFIER {;}
          	| PostfixExpr INC_OP {;}
          	| PostfixExpr DEC_OP {;}
          	;

PrimaryExpr: CONSTANT {$$=new PrimaryExpr("int", $1);}
             |IDENTIFIER {$$ = new PrimaryExpr("identif",$1);}
             ;

UnaryOp: '&'	{ $$ = '&'; }
        | '*'	{ $$ = '*'; }
        | '+'	{ $$ = '+'; }
        | '-'	{ $$ = '-'; }
        | '~'	{ $$ = '~'; }
        | '!'	{ $$ = '!';}
        ;


%%

const TranslationalUnit* g_root; // Definition of variable (to match declaration earlier)

const TranslationalUnit *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
