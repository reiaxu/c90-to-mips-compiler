#ifndef ast_assignexpr_hpp
#define ast_assignexpr_hpp

#include "ast_transalationalunit.hpp"
#include "MIPSish.hpp"
#include "context.hpp"

#include <string>
#include<map>
#include<iostream>

class AssignExpr
    :public TranslationalUnit{

   private:
    TransUnitPtr unaryexpr;
    int op;
    TransUnitPtr assexpr;

public:
    AssignExpr(TransUnitPtr unaryexpr_,int op_, TransUnitPtr assexpr_):unaryexpr(unaryexpr_),op(op_),assexpr(assexpr_){}


    ~AssignExpr() override{
        delete assexpr;
        delete unaryexpr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
            unaryexpr->PrettyPrint(dst);
            dst<<" "<<char(op)<<" ";
            assexpr->PrettyPrint(dst);
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      //todo;
    };

};



#endif
