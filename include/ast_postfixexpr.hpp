#ifndef ast_postfixexpr_hpp
#define ast_postfixexpr_hpp

#include"ast_transalationalunit.hpp"

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

    ~PostfixExpr() override{
        delete postfixptr;
        delete identif;
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

        else if(op == 0){
            postfixptr->PrettyPrint(dst);
            dst<<" () ";
        }
    }

};



#endif