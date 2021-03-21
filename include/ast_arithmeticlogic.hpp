#ifndef ast_arithmeticlogic_hpp
#define ast_arithmeticlogic_hpp

#include"ast_transalationalunit.hpp"
#include "context.hpp"
#include "MIPSish.hpp"

#include<string>
#include<map>
#include<iostream>

class ArLoExpr
  :public TranslationalUnit{

  private:
    TransUnitPtr lhs;
    TransUnitPtr rhs;
    int optype;

  public:
    ArLoExpr(TransUnitPtr _lhs, TransUnitPtr _rhs, int op)
      :lhs(_lhs),rhs(_rhs),optype(op){}

    virtual ~ArLoExpr(){
      delete lhs;
      delete rhs;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      switch(optype){
        // LEFT_OP
        case(265):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" << ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // RIGHT_OP
        case(266):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" >> ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // LE_OP
        case(267):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" <= ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // GE_OP
        case(268):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" >= ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // EQ_OP
        case(269):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" == ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // NE_OP
        case(270):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" != ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // AND_OP
        case(271):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" && ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        // OR_OP
        case(272):
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" || ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

        default:
          dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" "<<char(optype)<<" ";
          rhs->PrettyPrint(dst);
          dst<<")";
          break;

      }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      std::string left = "$t0";
      std::string right = "$t1";
      switch(optype){

        case((int)'&'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_and(dst, destReg, left, right);
        break;

        case((int)'|'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_or(dst, destReg, left, right);
        break;

        case((int)'^'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_xor(dst, destReg, left, right);
        break;

        case((int)'*'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_mul(dst, destReg, left, right);
        break;

        case((int)'/'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_div(dst, destReg, left, right);
        break;

        case((int)'%'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_modu(dst, destReg, left, right);
        break;

        case((int)'+'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_add(dst, destReg, left, right);
        break;

        case((int)'-'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_sub(dst, destReg, left, right);
        break;

        case((int)'<'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_slt(dst, destReg, left, right);
        break;

        case((int)'>'):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_slt(dst, destReg, right, left);
        break;

        // LEFT_OP
        case(265):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_sll(dst, destReg, left, right);
        break;

        // RIGHT_OP
        case(266):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_srl(dst, destReg, left, right);
        break;

        // LE_OP
       case(267):

       break;

        // GE_OP
        case(268):

        break;

        // EQ_OP
        case(269):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_eq(dst, destReg, left, right);
        break;

        // NE_OP
        case(270):
        lhs->toMIPS(dst, left, context);
        rhs->toMIPS(dst, right, context);
        o_neq(dst, destReg, left, right);
        break;

        // AND_OP
        case(271):

        break;

        // OR_OP
        case(272):

        break;

        default:
          /*dst<<"(";
          lhs->PrettyPrint(dst);
          dst<<" "<<char(optype)<<" ";
          rhs->PrettyPrint(dst);
          dst<<")";*/
        break;

      }
    }
  };

#endif
