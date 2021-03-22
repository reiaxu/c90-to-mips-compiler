#ifndef ast_statementlist_hpp
#define ast_statementlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class StatList
      :public TranslationalUnit{
  private:
  TransUnitPtr statlist;
  TransUnitPtr stat;

  protected:

public:
  StatList(TransUnitPtr statlist_, TransUnitPtr stat_): statlist(statlist_), stat(stat_){}

  virtual ~StatList(){
    delete statlist;
    delete stat;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    statlist->PrettyPrint(dst);
    dst<<" ";
    stat->PrettyPrint(dst);
  }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      statlist->toMIPS(dst, destReg, context);
      stat->toMIPS(dst, destReg, context);
    }
};

#endif
