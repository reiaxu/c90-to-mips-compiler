%code requires{
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

%token TYPEDEF EXTERN STATIC
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOID
%token STRUCT ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

// %type <tu> ParameterDeclaration primary_expression postfix_expression ArgExprList UnaryExpr multiplicative_expression AdditiveExpr ShiftExpr
// %type <tu> RelationalExpr EqualityExpr ANDExpr XORExpr ORExpr LogicalANDExpr LogicalORExpr
// %type <tu> ParameterList CondExpr AssignExpr Expr ConstantExpr Declaration DeclarationSpec InitDeclaratorList InitDeclarator
// %type <tu> ParameterTypeList  StorageClassSpec TypeSpec  Declarator DirectDeclarator Initializer InitializerList LabeledStatement CompoundStatement DeclarationList StatementList ExpressionStatement SelectionStatement IterationStatement jump_statement Statement translation_unit function_definition
// %type <string> IDENTIFIER CONSTANT STRING_LITERAL
// %type <number> unary_operator Pointer
// %type <en_ass> AssignOp
// %type <tu> AbstractDeclarator DirectAbstractDeclarator SpecQualifierList TypeName

%type <tu> ROOT TranslationalUnit ExternalDec FunctionDef
%type <tu> StatementList Statement CompoundStatement JumpStatement LabeledStatement ExpressionStatement IterationStatement SelectionStatement
%type <tu> Expr AssignExpr ConstantExpr CondExpr LogicalORExpr LogicalANDExpr ORExpr XORExpr ANDExpr EqualityExpr RelationalExpr ShiftExpr AdditiveExpr MultiplicativeExpr UnaryExpr PostfixExpr PrimaryExpr ParameterDeclaration ArgExprList
%type <tu> DeclarationList Declaration DeclarationSpec TypeName TypeSpec SpecQualifierList StorageClassSpec
%type <tu> ParameterTypeList ParameterList Identifierlist InitDeclaratorList InitDeclarator InitializerList Initializer DirectDeclarator Declarator
%type <string> IDENTIFIER CONSTANT STRING_LITERAL 
%type <number> AssignOp

%type <_char> UnaryOp Pointer

%start ROOT
%%

ROOT: TranslationalUnit {g_root = $1;}

TranslationalUnit: ExternalDec {$$ = $1;}
                 | TranslationalUnit ExternalDec {;}
                 ;

ExternalDec: FunctionDef {$$=$1;}
           | Declaration {;}
           ;

FunctionDef: DeclarationSpec Declarator CompoundStatement {$$ = new FunctionDef($1, $2, $3);}
           | Declarator CompoundStatement {$$ = new FunctionDef(NULL, $1, $2);}
           ;

StatementList: Statement {$$=$1;}
             | StatementList Statement {$$ = new StatList($1, $2);}
             ;

Statement: LabeledStatement {$$=$1;}
         | JumpStatement {$$=$1;}
         | CompoundStatement {$$=$1;}
         | ExpressionStatement {$$=$1;}
         | IterationStatement {$$=$1;}
         | SelectionStatement {$$=$1;}
         ;

SelectionStatement: IF '(' Expr ')' Statement {$$ = new SelStat(302, $3, $5);}
                  | IF '(' Expr ')' Statement ELSE Statement {$$ = new SelStat(303, $3, $5, $7);}
                  | SWITCH '(' Expr ')' Statement {$$ = new SelStat(304, $3, $5);}
                  ;

IterationStatement: WHILE '(' Expr ')' Statement {$$ = new IterStat(305, $3, $5);}
                  | DO Statement WHILE '(' Expr ')' ';' {$$ = new IterStat(306, $5, $2);}
                  | FOR '(' ExpressionStatement ExpressionStatement ')' Statement {$$ = new IterStat(307, $3, $4, NULL, $6);}
                  | FOR '(' ExpressionStatement ExpressionStatement Expr')' Statement {$$ = new IterStat(307, $3, $4, $5, $7);}
                  ;

ExpressionStatement: ';' {$$ = new ExprStat(NULL);}
                   | Expr ';' {$$ = new ExprStat($1);}
                   ;

CompoundStatement: '{' '}' {$$=new CompoundStat(NULL, NULL);}
                 | '{' StatementList '}' {$$=new CompoundStat(NULL, $2);}
                 | '{' DeclarationList '}' {$$=new CompoundStat($2, NULL);}
                 | '{' DeclarationList StatementList '}' {$$=new CompoundStat($2, $3);}
                 ;

JumpStatement: RETURN Expr ';' {$$ = new JumpStat("return",$2);}
             | RETURN ';' {$$ = new JumpStat("return");}
             | CONTINUE ';' {$$ = new JumpStat("continue");}
             | BREAK ';' {$$ = new JumpStat("break");}
             ;

LabeledStatement: IDENTIFIER ':' Statement {;}
                | CASE ConstantExpr ':' Statement {;}
                | DEFAULT ':' Statement {;}
                ;

/*struct and enum stuff start
StructSpec
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: SpecQualifierList struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: Declarator
	| ':' ConstantExpr
	| Declarator ':' ConstantExpr
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
	| IDENTIFIER '=' ConstantExpr
	;
struct and enum stuff end*/

ParameterTypeList: ParameterList {$$=$1;}
                 ;

ParameterList: ParameterDeclaration {$$=$1;}
             | ParameterList ',' ParameterDeclaration {;}
             ;

ParameterDeclaration: DeclarationSpec Declarator {;}
                     | DeclarationSpec AbstractDeclarator {;}
                     | DeclarationSpec {$$=$1;}
                     ;

Identifierlist: IDENTIFIER {;}
            	| Identifierlist ',' IDENTIFIER {}
            	;

TypeName: SpecQualifierList {$$=$1;}
  	    | SpecQualifierList AbstractDeclarator {;}
  	    ;

SpecQualifierList: TypeSpec {$$=$1;}
                 | TypeSpec SpecQualifierList {;}
              	 ;

DirectAbstractDeclarator: '(' AbstractDeclarator ')' {;}
                        | '[' ']' {;}
                        | '[' ConstantExpr ']' {;}
                        | DirectAbstractDeclarator '[' ']' {;}
                        | DirectAbstractDeclarator '[' ConstantExpr ']' {;}
                        | '(' ')' {;}
                        | '(' ParameterTypeList ')' {;}
                        | DirectAbstractDeclarator '(' ')' {;}
                        | DirectAbstractDeclarator '(' ParameterTypeList ')' {;}
                        ;

AbstractDeclarator: Pointer {;}
                	| DirectAbstractDeclarator {;}
                	| Pointer DirectAbstractDeclarator {;}
                	;

DeclarationList: Declaration {$$=$1;}
              	| DeclarationList Declaration {;}
              	;

Declaration: DeclarationSpec ';' {;}
           | DeclarationSpec InitDeclaratorList ';' {;}
           ;

DeclarationSpec: TypeSpec {$$=$1;}
               | TypeSpec DeclarationSpec {; }
               | StorageClassSpec {$$=$1;}
               | StorageClassSpec DeclarationSpec {;}
               ;

InitDeclaratorList: InitDeclarator {$$=$1;}
                	| InitDeclaratorList ',' InitDeclarator {$$ = new InitDeclList($1, $3);}
                 	;

InitDeclarator: Declarator {$$= new InitDecl($1, NULL);}
            	| Declarator '=' Initializer {$$= new InitDecl($1, $3);}
            	;

Declarator: DirectDeclarator {$$=$1;}
          | Pointer DirectDeclarator {;}
          ;

DirectDeclarator: IDENTIFIER {$$ = new DirectDecl(0,$1);}
  | DirectDeclarator '(' ')' {$$ = new DirectDecl(1,$1);}
  | '(' Declarator ')' {$$ = new DirectDecl(2,$2);}
  | DirectDeclarator '[' ConstantExpr ']' {$$ = new DirectDecl(3,$1, $3);}
  | DirectDeclarator '[' ']' {$$ = new DirectDecl(4,$1);}
  | DirectDeclarator '(' ParameterTypeList ')' {$$ = new DirectDecl(5,$1, $3);}
  ;

StorageClassSpec: TYPEDEF {;}
                | EXTERN {;}
                ;

TypeSpec: INT {$$ =new TypeSpec("int");}
        | VOID {$$ =new TypeSpec("void");}
      	| CHAR {$$ =new TypeSpec("char");}
      	| SHORT {$$ =new TypeSpec("short");}
      	| LONG {$$ =new TypeSpec("long");}
      	| FLOAT {$$ =new TypeSpec("float");}
      	| DOUBLE {$$ =new TypeSpec("double");}
      	| SIGNED {$$ =new TypeSpec("signed");}
      	| UNSIGNED {$$ =new TypeSpec("unsigned");}
//      	| StructSpec {$$ =new TypeSpec("");}
//      	| enum_specifier {$$ =new TypeSpec("");}
//       	| TYPE_NAME {$$ =new TypeSpec("");}
      	;

Pointer: '*' {;}
       | '*' Pointer {;}
       ;

//---------------------------------------------------------------
InitializerList: Initializer {$$=$1;}
               | InitializerList ',' Initializer {;}
            	 ;

Initializer: AssignExpr {$$=$1;}
	         | '{' InitializerList '}' {;}
	         | '{' InitializerList ',' '}' {;}
	         ;

ConstantExpr: CondExpr {$$=$1;}
	          ;

ArgExprList: AssignExpr {$$=$1;}
           | ArgExprList ',' AssignExpr {;}
           ;

Expr: AssignExpr {$$=$1;}
    ;

AssignExpr: CondExpr {$$=$1;}
        	| UnaryExpr AssignOp AssignExpr {/*$$ = new AssignExpr($1, $2, $3)*/;}
        	;

CondExpr: LogicalORExpr {$$=$1;}
        | LogicalORExpr '?' Expr ':' CondExpr {/*$$ = new CondExpr($1, $3, $5)*/;}
      	;

LogicalORExpr: LogicalANDExpr {$$=$1;}
             | LogicalORExpr OR_OP LogicalANDExpr {$$ = new ArLoExpr($1, $3, 272);}
             ;

LogicalANDExpr: ORExpr {$$=$1;}
            	| LogicalANDExpr AND_OP ORExpr {$$ = new ArLoExpr($1, $3, 271);}
            	;

ORExpr: XORExpr {$$=$1;}
    	| ORExpr '|' XORExpr {$$ = new ArLoExpr($1, $3, int('|'));}
    	;

XORExpr: ANDExpr {$$=$1;}
       | XORExpr '^' ANDExpr {$$ = new ArLoExpr($1, $3, int('^'));}
       ;

ANDExpr: EqualityExpr  {$$=$1;}
    	 | ANDExpr '&' EqualityExpr {$$ = new ArLoExpr($1, $3, int('&'));}
       ;

EqualityExpr: RelationalExpr {$$=$1;}
          	| EqualityExpr EQ_OP RelationalExpr {$$ = new ArLoExpr($1, $3, 269);}
          	| EqualityExpr NE_OP RelationalExpr {$$ = new ArLoExpr($1, $3, 270);}
          	;

RelationalExpr: ShiftExpr {$$=$1;}
              | RelationalExpr '<' ShiftExpr {$$ = new ArLoExpr($1, $3, int('<'));}
              | RelationalExpr '>' ShiftExpr {$$ = new ArLoExpr($1, $3, int('>'));}
              | RelationalExpr LE_OP ShiftExpr {$$ = new ArLoExpr($1, $3, 267);}
              | RelationalExpr GE_OP ShiftExpr {$$ = new ArLoExpr($1, $3, 268);}
              ;

ShiftExpr: AdditiveExpr {$$=$1;}
	       | ShiftExpr LEFT_OP AdditiveExpr {$$ = new ArLoExpr($1, $3, 265);}
	       | ShiftExpr RIGHT_OP AdditiveExpr {$$ = new ArLoExpr($1, $3, 266);}
	       ;

AdditiveExpr: MultiplicativeExpr {$$=$1;}
          	| AdditiveExpr '+' MultiplicativeExpr {$$ = new ArLoExpr($1, $3, int('+'));}
          	| AdditiveExpr '-' MultiplicativeExpr {$$ = new ArLoExpr($1, $3, int('-'));}
          	;

MultiplicativeExpr: UnaryExpr {$$=$1;}
                	| MultiplicativeExpr '*' UnaryExpr {$$ = new ArLoExpr($1, $3, int('*'));}
                	| MultiplicativeExpr '/' UnaryExpr {$$ = new ArLoExpr($1, $3, int('/'));}
                	| MultiplicativeExpr '%' UnaryExpr {$$ = new ArLoExpr($1, $3, int('%'));}
                	;

UnaryExpr: PostfixExpr {$$=$1;}
        	| INC_OP UnaryExpr {$$ = new UnaryExpr(263, $2);}
        	| DEC_OP UnaryExpr {$$ = new UnaryExpr(264, $2);}
        	| UnaryOp UnaryExpr {$$ = new UnaryExpr(int($1), $2);}
        	| SIZEOF UnaryExpr {;}
        	| SIZEOF '(' TypeName ')' {;}
        	;

PostfixExpr: PrimaryExpr {$$=$1;}
            | PostfixExpr '[' Expr ']' {;}
          	| PostfixExpr '(' ')' {$$ = new PostfixExpr($1, 0);}
            | PostfixExpr '(' ArgExprList ')' {;}
          	| PostfixExpr '.' IDENTIFIER {$$ = new PostfixExpr($1, $3, int('.'));}
          	| PostfixExpr PTR_OP IDENTIFIER {$$ = new PostfixExpr($1, $3, 262);}
          	| PostfixExpr INC_OP {$$ = new PostfixExpr($1, 263);}
          	| PostfixExpr DEC_OP {$$ = new PostfixExpr($1, 264);}
          	;

PrimaryExpr: CONSTANT {$$=new PrimaryExpr("int", $1);}
           | IDENTIFIER {$$ = new PrimaryExpr("identif",$1);}
           | STRING_LITERAL {$$ = new PrimaryExpr("string",$1);}
           | '(' Expr ')' {$$ = new PrimaryExpr("expr",$2);}
           ;

AssignOp: '=' {$$=int('=');}
        | MUL_ASSIGN {$$=MUL_ASSIGN;}
       	| DIV_ASSIGN {$$=DIV_ASSIGN;}
      	| MOD_ASSIGN {$$=MOD_ASSIGN;}
       	| ADD_ASSIGN {$$=ADD_ASSIGN;}
        | SUB_ASSIGN {$$=SUB_ASSIGN;}
      	| LEFT_ASSIGN {$$=LEFT_ASSIGN;}
        | RIGHT_ASSIGN {$$=RIGHT_ASSIGN;}
        | AND_ASSIGN {$$=AND_ASSIGN;}
        | XOR_ASSIGN {$$=XOR_ASSIGN;}
        | OR_ASSIGN {$$=OR_ASSIGN;}
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
