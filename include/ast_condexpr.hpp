#ifndef ast_condexpr_hpp
#define ast_condexpr_hpp

#include "ast_transalationalunit.hpp"
#include <string>
#include<map>
#include<iostream>

class CondExpr
    :public TranslationalUnit{

   private:
    TransUnitPtr or_expr;
    TransUnitPtr expr;
    TransUnitPtr cond_expr;

public:
    CondExpr(TransUnitPtr or_expr_, TransUnitPtr expr_, TransUnitPtr cond_expr_):or_expr(or_expr_),expr(expr_), cond_expr(cond_expr_){}

    ~CondExpr() override{
        delete or_expr;
        delete expr;
        delete cond_expr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        or_expr->PrettyPrint(dst);
        dst<<" ? ";
        expr->PrettyPrint(dst);
        dst<<" : ";
        cond_expr->PrettyPrint(dst);
    }

};



#endif