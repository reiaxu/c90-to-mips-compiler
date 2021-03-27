#ifndef ast_selstat_hpp
#define ast_selstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class SelStat
      :public TranslationalUnit{
  private:
  int type;
  TransUnitPtr expr;
  TransUnitPtr stat1;
  TransUnitPtr stat2;

  protected:

public:
  SelStat(int op_, TransUnitPtr expr_, TransUnitPtr stat1_): type(op_), expr(expr_), stat1(stat1_){}
  SelStat(int op_, TransUnitPtr expr_, TransUnitPtr stat1_, TransUnitPtr stat2_): type(op_), expr(expr_), stat1(stat1_), stat2(stat2_){}

  virtual ~SelStat(){
    delete expr;
    delete stat1;
    delete stat2;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(type==1){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
    }
    else if (type==2){
      dst<<"if (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
      dst<<std::endl;
      dst<<" else ";
      stat2->PrettyPrint(dst);
    }
    else if (type==3){
      dst<<"switch (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat1->PrettyPrint(dst);
    }
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      std::string tempR = "$t0";
      if(type==1){
        expr->toMIPS(dst, tempR, context);
        std::string _label = genUL(context.getScopeName());
        o_beq(dst, tempR, "$zero", _label);
        stat1->toMIPS(dst, destReg, context);
        dst<<_label<<":"<<std::endl;
        //TODO: consider a JumpStat as stat1 :(
      }else if(type==2){
        expr->toMIPS(dst, tempR, context);
        std::string _labelT = genUL(context.getScopeName());
        std::string _labelF = genUL(context.getScopeName());
        o_beq(dst, tempR, "$zero", _labelF);
        stat1->toMIPS(dst, destReg, context);
        o_b(dst, _labelT);
        dst<<_labelF<<":"<<std::endl;
        stat2->toMIPS(dst, destReg, context);
        dst<<_labelT<<":"<<std::endl;
      }else if(type==3){
        //todo 
      }
    }
};

#endif
