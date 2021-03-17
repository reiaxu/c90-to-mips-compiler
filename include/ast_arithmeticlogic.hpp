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

      //  case 1:

      //    break;

      //  case 2:

      //    break;

      }
    }
  };

#endif
