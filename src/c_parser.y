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
%type <tu> AdditiveExpr MultiplicativeExpr UnaryExpr PostfixExpr PrimaryExpr
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

declaration: declaration_specifiers ';'
          	| declaration_specifiers init_declarator_list ';'
          	;

DeclarationSpecifier: storage_class_specifier
                  	| storage_class_specifier declaration_specifiers
                  	| type_specifier
                  	| type_specifier declaration_specifiers
                  	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

TypeSpecifier: INT {$$ =new TypeSpec("int");}
	| VOID
	| CHAR
	| SHORT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: Struct IDENTIFIER '{' struct_declaration_list '}'
	| Struct '{' struct_declaration_list '}'
	| Struct IDENTIFIER
	;

Struct
	: STRUCT
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

Declarator: DirectDeclarator {$$=$1;}
          | pointer direct_declarator
          ;

DirectDeclarator: IDENTIFIER {$$ = $1;}
                | DirectDeclarator '(' ')' {$$=$1;}
              	| '(' declarator ')'
              	| direct_declarator '[' constant_expression ']'
              	| direct_declarator '[' ']'
              	| direct_declarator '(' parameter_type_list ')'
              	| direct_declarator '(' identifier_list ')'
              	;

pointer
	: '*'
	| '*' pointer
	;


parameter_type_list
	: parameter_list
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;


constant_expression
	: conditional_expression
	;

expression
	: assignment_expression
  ;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;


logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;


exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;


shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

AdditiveExpr: MultiplicativeExpr {$$=$1;}
          	| AdditiveExpr '+' MultiplicativeExpr {;}
          	| AdditiveExpr '-' MultiplicativeExpr {;}
          	;

MultiplicativeExpr: UnaryExpr {$$=$1;}
                	| MultiplicativeExpr '*' UnaryExpr {}
                	| MultiplicativeExpr '/' UnaryExpr {}
                	| MultiplicativeExpr '%' UnaryExpr {}
                	;

UnaryExpr: PostfixExpr {$$=$1;}
        	| INC_OP UnaryExpr {;}
        	| DEC_OP UnaryExpr {;}
        	| UnaryOp UnaryExpr {;}
        	| SIZEOF UnaryExpr {;}
        	| SIZEOF '(' type_name ')' {;}
        	;

PostfixExpr: PrimaryExpr {$$=$1;}
            | PostfixExpr '[' expression ']' {;}
          	| PostfixExpr '(' ')' {;}
            | PostfixExpr '(' argument_expression_list ')' {;}
          	| PostfixExpr '.' IDENTIFIER {;}
          	| PostfixExpr PTR_OP IDENTIFIER {;}
          	| PostfixExpr INC_OP {;}
          	| PostfixExpr DEC_OP {;}
          	;

PrimaryExpr: CONSTANT {$$=new PrimaryExpr("int", $1);}
             |IDENTIFIER {$$ = new PrimaryExpr("identif",$1);}
             ;

AssignOp: '=' {}
        | MUL_ASSIGN {}
       	| DIV_ASSIGN {}
      	| MOD_ASSIGN {}
       	| ADD_ASSIGN {}
        | SUB_ASSIGN {}
    	  | LEFT_ASSIGN {}
        | RIGHT_ASSIGN {}
        | AND_ASSIGN {}
        | XOR_ASSIGN {}
        | OR_ASSIGN {}
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
