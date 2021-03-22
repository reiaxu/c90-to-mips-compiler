#ifndef ast_argexprlist_hpp
#define ast_argexprlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class ArgExprList
    : public TranslationalUnit{
    
    private:
    TransUnitPtr list;
    TransUnitPtr expr;

public:
    ArgExprList(TransUnitPtr list_, TransUnitPtr expr_):list(list_),expr(expr_){}

    ~ArgExprList() override{
        delete list;
        delete expr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        
        list->PrettyPrint(dst);
        dst<<", ";
        expr->PrettyPrint(dst);
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
        //todo
  }

};



#endif