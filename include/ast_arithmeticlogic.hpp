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
          lhs->PrettyPrint(dst);
          dst<<" << ";
          rhs->PrettyPrint(dst);
          break;

        // RIGHT_OP
        case(266):
          lhs->PrettyPrint(dst);
          dst<<" >> ";
          rhs->PrettyPrint(dst);
          break;

        // LE_OP
        case(267):
          lhs->PrettyPrint(dst);
          dst<<" <= ";
          rhs->PrettyPrint(dst);
          break;

        // GE_OP
        case(268):
          lhs->PrettyPrint(dst);
          dst<<" >= ";
          rhs->PrettyPrint(dst);
          break;

        // EQ_OP
        case(269):
          lhs->PrettyPrint(dst);
          dst<<" == ";
          rhs->PrettyPrint(dst);
          break;

        // NE_OP
        case(270):
          lhs->PrettyPrint(dst);
          dst<<" != ";
          rhs->PrettyPrint(dst);
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
  };

#endif
