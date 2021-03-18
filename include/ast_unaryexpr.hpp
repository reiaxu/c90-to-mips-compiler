#ifndef ast_unaryexpr_hpp
#define ast_unaryexpr_hpp

#include "ast_transalationalunit.hpp"
#include <string>
#include<map>
#include<iostream>

class UnaryExpr
    :public TranslationalUnit{

   private:
    int prefix;
    TransUnitPtr unaryexpr;

public:
    UnaryExpr(int u, TransUnitPtr p):prefix(u),unaryexpr(p){}


    ~UnaryExpr() override{

        delete unaryexpr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{

        if(prefix<258){
            dst<<char(prefix);
            unaryexpr->PrettyPrint(dst);
        }else{
            // inc op
            if (prefix==263) {
                dst<<"++";
                unaryexpr->PrettyPrint(dst);
            }

            // dec op
            if (prefix==264) {
                dst<<"--";
                unaryexpr->PrettyPrint(dst);
            }
        }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg) const override;

};



#endif
