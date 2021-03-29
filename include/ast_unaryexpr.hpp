#ifndef ast_unaryexpr_hpp
#define ast_unaryexpr_hpp

#include "ast_transalationalunit.hpp"
#include"ast_primaryexpr.hpp"
#include"ast_typespec.hpp"

#include "MIPSish.hpp"
#include "context.hpp"

#include <string>
#include<map>
#include<iostream>

class UnaryExpr
    :public TranslationalUnit{

   private:
    int prefix;
    TransUnitPtr unaryexpr;
    TransUnitPtr tn;

public:
    UnaryExpr(int u, TransUnitPtr p):prefix(u),unaryexpr(p){}
    UnaryExpr(int u, TransUnitPtr p, TransUnitPtr t):prefix(u),unaryexpr(p),tn(t){}

    ~UnaryExpr() override{

        delete unaryexpr;
        delete tn;
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
            if (prefix==201 && tn==NULL){
              dst<<"sizeof ";
              unaryexpr->PrettyPrint(dst);
            }
            if (prefix==201 && unaryexpr==NULL){
              dst<<"sizeof (";
              tn->PrettyPrint(dst);
              dst<<") ";
            }
        }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      std::string unarytemp = "$t0";
      std::string var_name;
      std::string _offset;
      PrimaryExpr *_castedpe;
      switch(prefix){
        case(int('!')):
          //unsure abt implementation, didnt include addiu like in godbolt
          unaryexpr->toMIPS(dst, unarytemp, context);
          //treat it as unsiged so that it just takes absolute value! in that way only 0 will be less than 1
          o_sltiu(dst, destReg, unarytemp, "1");
        break;

        case(int('~')):
          unaryexpr->toMIPS(dst, unarytemp, context);
          o_subu(dst, destReg, "$0", unarytemp);
        break;

        case(int('-')):
          unaryexpr->toMIPS(dst, unarytemp, context);
          o_subu(dst, destReg, "$0", unarytemp);
        break;

        case(int('+')):
          //kinda like a do nothing for unary exprs?
          unaryexpr->toMIPS(dst, destReg, context);
        break;

        case(int('*')):
          //TODO: pointer stuff
        break;

        case(int('&')):
          //TODO: addressof stuff? naive implementation just li destReg getOffset($fp)?

        break;

        // ++x
        case(int(263)):
        unaryexpr->toMIPS(dst, unarytemp, context);
        o_addiu(dst, unarytemp, unarytemp, "1");
        _castedpe = (PrimaryExpr*) unaryexpr;
        var_name = _castedpe->getName();
        _offset = std::to_string(context->getOffset(var_name));
        o_sw(dst, unarytemp, _offset, "$fp");
        break;

        // --x
        case(int(264)):
        unaryexpr->toMIPS(dst, unarytemp, context);
        o_addiu(dst, unarytemp, destReg, "-1");
        _castedpe = (PrimaryExpr*) unaryexpr;
        var_name = _castedpe->getName();
        _offset = std::to_string(context->getOffset(var_name));
        o_sw(dst, unarytemp, _offset, "$fp");
        break;

        case(int(261)):
        if (tn==NULL){
          o_li(dst, destReg, "4");
        }
        else if (unaryexpr==NULL){
          TypeSpec *_casted = (TypeSpec*) tn;
          std::string type = _casted->getType();
          if (type=="int" || type=="float" || type=="unsigned" || type=="signed"){
            o_li(dst, destReg, "4");
          }
          else if (type=="char" || type=="void"){
            o_li(dst, destReg, "1");
          }
          else if (type=="short"){
            o_li(dst, destReg, "2");
          }
          else if (type=="double" || type=="long"){
            o_li(dst, destReg, "8");
          }
        } 
        }
      }

};



#endif
     /*if(unaryexpr->getType()=="int"){
        switch(prefix){
          case(int(!)):
            dst<<"li"<<' '+destReg+' '<<!(*val);
          break;

          case(int(~)):
            dst<<"li"<<' '+destReg+' '<<~(*val);
          break;

          case(int(-)):
            dst<<"li"<<' '+destReg+' '<<-(*val);
          break;

          case(int(+)):
            dst<<"li"<<' '+destReg+' '<<(*val);
          break;

          case(int(*)):
            //TODO
          break;

          case(int(&)):
            //TODO
          break;
        }*/