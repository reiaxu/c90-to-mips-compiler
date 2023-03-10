#ifndef ast_postfixexpr_hpp
#define ast_postfixexpr_hpp

#include"ast_transalationalunit.hpp"
#include"ast_primaryexpr.hpp"
#include "MIPSish.hpp"
#include "context.hpp"

#include<string>
#include<map>
#include<iostream>


class PostfixExpr
    : public TranslationalUnit{

    private:
    TransUnitPtr postfixptr;
    TransUnitPtr aexpr;
    std::string* identif=0;
    int op;

public:
    PostfixExpr(TransUnitPtr postfixptr_, int op_):postfixptr(postfixptr_),op(op_){}
    PostfixExpr(TransUnitPtr postfixptr_, TransUnitPtr aexpr_, int op_):postfixptr(postfixptr_),aexpr(aexpr_),op(op_){}
    PostfixExpr(TransUnitPtr postfixptr_, std::string* identif_, int op_):postfixptr(postfixptr_),identif(identif_),op(op_){}

    ~PostfixExpr() override{
        delete postfixptr;
        delete identif;
        delete aexpr;
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

    /*const std::string getName(){
      if(identif==0){
        return postfixptr->getName();
      }else{
        return *identif;
      }
    }*/

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      std::string postfixtemp = "$t0";
      std::string var_name;
      std::string _offset;
      PrimaryExpr *_castedpf;

        //x++
      if(op == 263){
            postfixptr->toMIPS(dst, postfixtemp, context);
            o_addiu(dst, destReg, postfixtemp, "1");
            _castedpf = (PrimaryExpr*) postfixptr;
            var_name = _castedpf->getName();
            _offset = std::to_string(context->getOffset(var_name));
            o_sw(dst, destReg, _offset, "$fp");
        }

      //x--
      else if(op == 264){
            postfixptr->toMIPS(dst, postfixtemp, context);
            o_addiu(dst, destReg, postfixtemp, "-1");
            _castedpf = (PrimaryExpr*) postfixptr;
            var_name = _castedpf->getName();
            _offset = std::to_string(context->getOffset(var_name));
            o_sw(dst, destReg, _offset, "$fp");
        }

        else if (op==0){
          //postfixptr->toMIPS(dst, postfixtemp, context);
          //dont think the above is needed since this is likely to be a function
          _castedpf = (PrimaryExpr*) postfixptr;
          var_name = _castedpf->getName();
          //_offset = std::to_string(context->getOffset(var_name));
          o_jal(dst, var_name);
          o_nop(dst);

          o_move(dst, destReg,"$2");
          //o_sw(dst, postfixtemp, _offset, "$fp");
        }
        else if (op==1){
          aexpr->toMIPS(dst, "$4", context);
          _castedpf = (PrimaryExpr*) postfixptr;
          var_name = _castedpf->getName();
          //_offset = std::to_string(context->getOffset(var_name));
          o_jal(dst, var_name);
          o_nop(dst);

          o_move(dst, destReg,"$2");
        }

    };


};



#endif
