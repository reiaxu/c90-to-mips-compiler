#ifndef ast_selstat_hpp
#define ast_selstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class SelStat
      :public TranslationalUnit{
  private:
  int op;
  TransUnitPtr expr;
  TransUnitPtr stat1;
  TransUnitPtr stat2;

  protected:

public:
  SelStat(int op_, TransUnitPtr expr_, TransUnitPtr stat1_): op(op_), expr(expr_), stat1(stat1_){}
  SelStat(int op_, TransUnitPtr expr_, TransUnitPtr stat1_, TransUnitPtr stat2_): op(op_), expr(expr_), stat1(stat1_), stat2(stat2_){}

  virtual ~SelStat(){
    delete expr;
    delete stat1;
    delete stat2;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(op==302){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
    }
    else if (op==303){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
      dst<<std::endl;
      dst<<" else ";
      stat2->PrettyPrint(dst);
    }
    else if (op==304){
      dst<<"switch (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
    }
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      //todo
    }
};

#endif
