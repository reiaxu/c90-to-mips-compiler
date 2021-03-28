#ifndef ast_iterationstat_hpp
#define ast_iterationstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class IterStat
      :public TranslationalUnit{
  private:
  int op;

  TransUnitPtr exprstat1;
  TransUnitPtr exprstat2;
  TransUnitPtr expr;
  TransUnitPtr stat;

  protected:

public:
  IterStat(int op_, TransUnitPtr expr_, TransUnitPtr stat_): op(op_), expr(expr_), stat(stat_){}
  IterStat(int op_, TransUnitPtr exprstat1_, TransUnitPtr exprstat2_, TransUnitPtr expr_, TransUnitPtr stat_): op(op_),exprstat1(exprstat1_), exprstat2(exprstat2_), expr(expr_), stat(stat_){}

  ~IterStat() override{
    delete expr;
    delete stat;
    delete exprstat1;
    delete exprstat2;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(op==305){
      dst<<"while (";
      expr->PrettyPrint(dst);
      dst<<") ";
      stat->PrettyPrint(dst);
    }
    else if (op==306){
      dst<<"do ";
      stat->PrettyPrint(dst);
      dst<<" while (";
      expr->PrettyPrint(dst);
      dst<<");";
      dst<<std::endl;
    }
    else if (op==307){
      if (expr==NULL){
        dst<<"for (";
        exprstat1->PrettyPrint(dst);
        dst<<" ";
        exprstat2->PrettyPrint(dst);
        dst<<") ";
        stat->PrettyPrint(dst);
      }
    }else if(op==308) {
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



  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
    std::string condR = "$t0";
    if(op==305){
      std::string _labelEx = genUL(context->getScopeName());
      std::string _labelS = genUL(context->getScopeName());

      dst<<_labelS<<":"<<std::endl;
      expr->toMIPS(dst, condR, context);

      o_beq(dst, condR, "$zero", _labelEx);
      o_nop(dst);

      stat->toMIPS(dst, destReg, context);

      o_b(dst,_labelS);
      o_nop(dst);

      dst<<_labelEx<<":"<<std::endl;

    }else if(op==306){
      std::string _labelEx = genUL(context->getScopeName());
      std::string _labelS = genUL(context->getScopeName());

      dst<<_labelS<<":"<<std::endl;
      stat->toMIPS(dst, destReg, context);

      expr->toMIPS(dst, condR, context);
      o_beq(dst, condR, "$zero", _labelEx);
      o_nop(dst);

      o_b(dst,_labelS);
      o_nop(dst);

      dst<<_labelEx<<":"<<std::endl;

    }else if(op==307){
      exprstat1->toMIPS(dst, condR, context);

      std::string _labelEx = genUL(context->getScopeName());
      std::string _labelS = genUL(context->getScopeName());

      dst<<_labelS<<":"<<std::endl;
      exprstat2->toMIPS(dst, condR, context);

      o_beq(dst, condR, "$zero", _labelEx);
      o_nop(dst);

      stat->toMIPS(dst, destReg, context);

      o_b(dst,_labelS);
      o_nop(dst);

      dst<<_labelEx<<":"<<std::endl;

    }else if(op==308){
      exprstat1->toMIPS(dst, condR, context);

      std::string _labelEx = genUL(context->getScopeName());
      std::string _labelS = genUL(context->getScopeName());

      dst<<_labelS<<":"<<std::endl;
      exprstat2->toMIPS(dst, condR, context);

      o_beq(dst, condR, "$zero", _labelEx);
      o_nop(dst);

      stat->toMIPS(dst, destReg, context);
      expr->toMIPS(dst, destReg, context);

      o_b(dst,_labelS);
      o_nop(dst);

      dst<<_labelEx<<":"<<std::endl;

    }
  }

};

#endif
