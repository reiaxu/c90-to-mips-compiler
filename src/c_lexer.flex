%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "c_parser.tab.hpp"
//#include "c_lexparse.hpp"
//#include<string>

void count();

%}
KEYWORD auto|break|float|signed|case|for|sizeof|char|static|if|struct|continue|inline|switch|default|int|typedef|do|long|double|register|unsigned|else|restrict|void|enum|return|volatile|extern|short|while

D			[0-9]
I			[a-zA-Z_][0-9a-zA-Z_]*
SLC   "//"

%%
"auto"		  	{ count(); return(AUTO); }
"break"			  { count(); return(BREAK); }
"case"	  		{ count(); return(CASE); }
"char"		  	{ count(); return(CHAR); }
"continue"		{ count(); return(CONTINUE); }
"default"		  { count(); return(DEFAULT); }
"do"			    { count(); return(DO); }
"double"		  { count(); return(DOUBLE); }
"else"			  { count(); return(ELSE); }
"enum"		  	{ count(); return(ENUM); }
"float"		  	{ count(); return(FLOAT); }
"for"		  	  { count(); return(FOR); }
"if"	    		{ count(); return(IF); }
"int"		    	{ count(); return(INT); }
"long"			  { count(); return(LONG); }
"register"		{ count(); return(REGISTER); }
"return"		  { count(); return(RETURN); }
"short"		 	  { count(); return(SHORT); }
"signed"	  	{ count(); return(SIGNED); }
"sizeof"  		{ count(); return(SIZEOF); }
"static"	  	{ count(); return(STATIC); }
"struct"		  { count(); return(STRUCT); }
"switch"		  { count(); return(SWITCH); }
"typedef"	  	{ count(); return(TYPEDEF); }
"unsigned"		{ count(); return(UNSIGNED); }
"void"			  { count(); return(VOID); }
"while"			  { count(); return(WHILE); }

{D}+          { yylval.string = new std::string(yytext); return CONSTANT; }
{I}           { yylval.string = new std::string(yytext); return IDENTIFIER; }

">>="	    		{ count(); return(RIGHT_ASSIGN); }
"<<="	    		{ count(); return(LEFT_ASSIGN); }
"+="	    		{ count(); return(ADD_ASSIGN); }
"-="	    		{ count(); return(SUB_ASSIGN); }
"*="	    		{ count(); return(MUL_ASSIGN); }
"/="	    		{ count(); return(DIV_ASSIGN); }
"%="    			{ count(); return(MOD_ASSIGN); }
"&="	    		{ count(); return(AND_ASSIGN); }
"^="	    		{ count(); return(XOR_ASSIGN); }
"|="	    		{ count(); return(OR_ASSIGN); }
">>"	    		{ count(); return(RIGHT_OP); }
"<<"	    		{ count(); return(LEFT_OP); }
"++"	    		{ count(); return(INC_OP); }
"--"	    		{ count(); return(DEC_OP); }
"->"	    		{ count(); return(PTR_OP); }
"&&"			    { count(); return(AND_OP); }
"||"			    { count(); return(OR_OP); }
"<="	    		{ count(); return(LE_OP); }
">="    			{ count(); return(GE_OP); }
"=="		    	{ count(); return(EQ_OP); }
"!="	  	  	{ count(); return(NE_OP); }
";"	      		{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","		      	{ count(); return(','); }
":"	      		{ count(); return(':'); }
"="		      	{ count(); return('='); }
"("	      		{ count(); return('('); }
")"	      		{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			      { count(); return('.'); }
"&"	      		{ count(); return('&'); }
"!"	      		{ count(); return('!'); }
"~"	      		{ count(); return('~'); }
"-"	      		{ count(); return('-'); }
"+"	      		{ count(); return('+'); }
"*"	      		{ count(); return('*'); }
"/"	      		{ count(); return('/'); }
"%"	      		{ count(); return('%'); }
"<"	      		{ count(); return('<'); }
">"	      		{ count(); return('>'); }
"^"	      		{ count(); return('^'); }
"|"	      		{ count(); return('|'); }
"?"	      		{ count(); return('?'); }

"//".*                     {fprintf(stderr, "Single line comment");}
"/*"((.|[\r\n])*)?"*/"     {fprintf(stderr, "Multiline comment");}

[ \t\v\n\f]   {/* fprintf(stderr, "Whitespace\n");*/ }
.             { fprintf(stderr, "Skipped : %s\n", yytext); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}