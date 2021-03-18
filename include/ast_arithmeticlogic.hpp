#ifndef ast_arithmeticlogic_hpp
#define ast_arithmeticlogic_hpp

#include"ast_transalationalunit.hpp"

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

    virtual void toMIPS(std::ostream &dst, std::string destReg) const override;
  };

#endif
