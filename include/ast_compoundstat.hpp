#ifndef ast_compoundstat_hpp
#define ast_compoundstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class CompoundStat
      :public TranslationalUnit{
  private:
  TransUnitPtr decl;
  TransUnitPtr statl;

  protected:

public:
  CompoundStat(TransUnitPtr decl_, TransUnitPtr statl_): decl(decl_), statl(statl_){}

  virtual ~CompoundStat(){
    delete decl;
    delete statl;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if ((decl == NULL) && (statl == NULL)) {
        dst<<"{} ";
    }
    else if ((decl == NULL) && (statl != NULL)) {
        dst<<"{";
        dst<<std::endl;
        statl->PrettyPrint(dst);
        dst<<std::endl;
        dst<<"} ";
    }
    else if ((decl != NULL) && (statl == NULL)) {
        dst<<"{";
        dst<<std::endl;
        decl->PrettyPrint(dst);
        dst<<std::endl;
        dst<<"} ";
    }
    else {
        dst<<"{";
        dst<<std::endl;
        decl->PrettyPrint(dst);
        dst<<" ";
        statl->PrettyPrint(dst);
        dst<<std::endl;
        dst<<"} ";
    }
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
    if ((decl == NULL) && (statl == NULL)) {
        //do nothing?
    }
    else if ((decl == NULL) && (statl != NULL)) {
        statl->toMIPS(dst, destReg, context);
    }
    else if ((decl != NULL) && (statl == NULL)) {
        //do stuff related to scope
        decl->toMIPS(dst, destReg, context);
    }
    else {
        decl->toMIPS(dst, destReg, context);
        statl->toMIPS(dst, destReg, context) ;
    }
  }
};

#endif
