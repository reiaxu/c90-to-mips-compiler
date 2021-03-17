#ifndef ast_exprstat_hpp
#define ast_exprstat_hpp

#include"ast_transalationalunit.hpp"

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
    expr->PrettyPrint(dst);
    dst<<';';
  }
};

#endif
