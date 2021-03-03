%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "c_lexparse.hpp"
#include<string>

extern TokenVal yylval;

%}
KEYWORD auto|break|float|signed|case|for|sizeof|char|static|if|struct|continue|inline|switch|default|int|typedef|do|long|double|register|unsigned|else|restrict|void|enum|return|volatile|extern|short|while

D			[0-9]
I			[a-zA-Z_][0-9a-zA-Z_]*
%%
"int" {return INT; }

"return" {  return RETURN; }

{D}+  { return INTCONST; }
{I} { return IDENTIFIER; }

";"	{ return(';'); }
"{" { return('{'); }
"}" { return('}'); }
","	{return(','); }
":"	{return(':'); }
"="	{return('='); }
"(" { return('('); }
")" { return(')'); }
"."	{return('.'); }
"&"	{return('&'); }
"!"	{return('!'); }
"~"	{return('~'); }
"-"	{return('-'); }
"+"	{return('+'); }
"*"	{return('*'); }
"/"	{return('/'); }
"%"	{return('%'); }
"<"	{return('<'); }
">"	{return('>'); }
"^"	{return('^'); }
"|"	{return('|'); }
"?"	{return('?'); }

[ \t\v\n\f]             { fprintf(stderr, "Whitespace\n"); }
.               { fprintf(stderr, "Skipped : %s\n", yytext); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
