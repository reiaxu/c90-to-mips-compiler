#ifndef ast_postfixexpr_hpp
#define ast_postfixexpr_hpp

#include"ast_transalationalunit.hpp"
#include "MIPSish.hpp"
#include "context.hpp"

#include<string>
#include<map>
#include<iostream>


class PostfixExpr
    : public TranslationalUnit{

    private:
    TransUnitPtr postfixptr;
    std::string* identif;
    int op;

public:
    PostfixExpr(TransUnitPtr postfixptr_, int op_):postfixptr(postfixptr_),op(op_){}
    PostfixExpr(TransUnitPtr postfixptr_, std::string* identif_, int op_):postfixptr(postfixptr_),identif(identif_),op(op_){}


    // PostfixExpr(std::string* t, TransUnitPtr p):type(t),ptr(p){} //case 0,2,6,7
    // PostfixExpr(std::string* t, TransUnitPtr p, std::string * i):type(t),ptr(p), id(i){} //case 4,5
    // PostfixExpr(std::string* t, TransUnitPtr p, TransUnitPtr o):type(t),ptr(p), op(o){} //case 1,3


    ~PostfixExpr() override{
        delete postfixptr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{

        if(op == 263){
            postfixptr->PrettyPrint(dst);
            dst<<"++";
        }
        else if (op == 264) {
            postfixptr->PrettyPrint(dst);
            dst<<"--";
        }
        else if (op == 262) {
            postfixptr->PrettyPrint(dst);
            dst<<"* ";
            dst<<(*identif);
        }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      int a = 3;
    };


};



#endif
