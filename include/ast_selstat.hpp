#ifndef ast_selstat_hpp
#define ast_selstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class SelStat
      :public TranslationalUnit{
  private:
  std::string ifstat;
  TransUnitPtr expr;
  TransUnitPtr stat1;
  TransUnitPtr stat2;

  protected:

public:
  SelStat(std::string if_, TransUnitPtr expr_, TransUnitPtr stat1_): ifstat(if_), expr(expr_), stat1(stat1_){}
  SelStat(std::string if_, TransUnitPtr expr_, TransUnitPtr stat1_, TransUnitPtr stat2_): ifstat(if_), expr(expr_), stat1(stat1_), stat2(stat2_){}

  virtual ~SelStat(){
    delete expr;
    delete stat1;
    delete stat2;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(ifstat=="if"){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
    }
    else if (ifstat=="ifelse"){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
      dst<<std::endl;
      dst<<" else ";
      stat2->PrettyPrint(dst);
    }
    else if (ifstat=="switch"){
      dst<<"switch (";
      expr->PrettyPrint(dst);
      dst<<") ";
      dst<<std::endl;
      stat1->PrettyPrint(dst);
    }
  }
};

#endif
