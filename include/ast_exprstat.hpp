#ifndef ast_exprstat_hpp
#define ast_exprstat_hpp

#include"ast_transalationalunit.hpp"
#include "MIPSish.hpp"

#include<string>
#include<map>
#include<iostream>

class ExprStat
      :public TranslationalUnit{
  private:
  TransUnitPtr expr;

  protected:

public:
  ExprStat(TransUnitPtr expr_): expr(expr_){}


  virtual ~ExprStat(){
    delete expr;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if (expr==NULL){
      dst<<"; ";
      dst<<std::endl;
    }
    else {
      expr->PrettyPrint(dst);
      dst<<"; ";
      dst<<std::endl;
    }

  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
    if (expr!=NULL){
      expr->toMIPS(dst, destReg, context);
    }
  }
};

#endif
