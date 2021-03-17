#ifndef ast_hpp
#define ast_hpp

#include "ast_transalationalunit.hpp"
#include "ast_functiondef.hpp"
#include "ast_typespec.hpp"
#include "ast_arithmeticlogic.hpp"
#include "ast_unaryexpr.hpp"
#include "ast_postfixexpr.hpp"
#include "ast_primaryexpr.hpp"
#include "ast_jumpstat.hpp"
#include "ast_condexpr.hpp"
#include "ast_assignexpr.hpp"
// #include "ast_selectionstat.hpp"

extern const TranslationalUnit* parseAST();

#endif
