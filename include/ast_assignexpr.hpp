#ifndef ast_assignexpr_hpp
#define ast_assignexpr_hpp

#include "ast_transalationalunit.hpp"
#include "ast_primaryexpr.hpp"
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

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      //todo;
       std::string assignR = "$t0";
       std::string assignR2 = "$t1";
       std::string var_name;
       std::string _offset;
       PrimaryExpr *_casted;
       

       assexpr->toMIPS(dst, assignR, context);
       _casted = (PrimaryExpr*) unaryexpr;
       var_name = _casted->getName();
       _offset = std::to_string(context->getOffset(var_name));
       
       if (op==int('=')){
            
            o_sw(dst, assignR, _offset, "$fp");
       }     
        if (op==273){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_mul(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }  
        if (op==274){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_div(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==275){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_modu(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==276){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_add(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==277){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_sub(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==278){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_sll(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==279){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_sra(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==280){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_and(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==281){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_xor(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
        if (op==282){
            o_lw(dst, assignR2, _offset, "$fp");
            o_nop(dst);

            o_or(dst, destReg, assignR, assignR2);
            o_sw(dst, destReg, _offset, "$fp");
        }
    }



};



#endif
