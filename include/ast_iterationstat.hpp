#ifndef ast_iterationstat_hpp
#define ast_iterationstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class IterStat
      :public TranslationalUnit{
  private:
  std::string whilestat;
  TransUnitPtr expr;
  TransUnitPtr stat;
  TransUnitPtr exprstat1;
  TransUnitPtr exprstat2;

  protected:

public:
  IterStat(std::string whilestat_, TransUnitPtr expr_, TransUnitPtr stat_): whilestat(whilestat_), expr(expr_), stat(stat_){}
  IterStat(TransUnitPtr exprstat1_, TransUnitPtr exprstat2_, TransUnitPtr stat_): exprstat1(exprstat1_), exprstat2(exprstat2_), stat(stat_){}
  IterStat(TransUnitPtr exprstat1_, TransUnitPtr exprstat2_, TransUnitPtr expr_, TransUnitPtr stat_): exprstat1(exprstat1_), exprstat2(exprstat2_), expr(expr_), stat(stat_){}

  virtual ~IterStat(){
    delete expr;
    delete stat;
    delete exprstat1;
    delete exprstat2;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(whilestat=="while"){
      dst<<whilestat<<" (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat->PrettyPrint(dst);
    }
    else if (whilestat=="do"){
      dst<<whilestat<<" ";
      stat->PrettyPrint(dst);
      dst<<" while (";
      expr->PrettyPrint(dst);
      dst<<");";
    }
    else if (expr == NULL){
      dst<<"for (";
      exprstat1->PrettyPrint(dst);
      dst<<" ";
      exprstat2->PrettyPrint(dst);
      dst<<") ";
      stat->PrettyPrint(dst);
    }
    else {
      dst<<"for (";
      exprstat1->PrettyPrint(dst);
      dst<<" ";
      exprstat2->PrettyPrint(dst);
      dst<<" ";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat->PrettyPrint(dst);
    }
  }
};

#endif
