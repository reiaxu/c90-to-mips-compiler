#ifndef ast_hpp
#define ast_hpp

#include "ast_transalationalunit.hpp"
#include "ast_nonabstransunit.hpp"
#include "ast_functiondef.hpp"
#include "ast_typespec.hpp"
#include "ast_arithmeticlogic.hpp"
#include "ast_unaryexpr.hpp"
#include "ast_postfixexpr.hpp"
#include "ast_primaryexpr.hpp"
#include "ast_jumpstat.hpp"
#include "ast_exprstat.hpp"
#include "ast_selstat.hpp"
#include "ast_iterationstat.hpp"
#include "ast_compoundstat.hpp"
//#include "ast_labeledstat.hpp"
#include "ast_condexpr.hpp"
#include "ast_assignexpr.hpp"
#include "ast_paramlist.hpp"
#include "ast_directdecl.hpp"
#include "ast_paramdecl.hpp"
#include "ast_argexprlist.hpp"
#include "ast_statementlist.hpp"
#include "ast_initdeclarator.hpp"
#include "ast_initdeclaratorlist.hpp"
#include "ast_declaration.hpp"
#include "ast_declarationlist.hpp"
#include "ast_initializerlist.hpp"
#include "ast_enumeratorlist.hpp"
#include "ast_enumspecifier.hpp"

extern const TranslationalUnit* parseAST(FILE* fp);

#endif
