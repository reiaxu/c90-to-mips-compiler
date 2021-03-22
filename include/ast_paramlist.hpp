#ifndef ast_paramlist_hpp
#define ast_paramlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class ParamList
      :public TranslationalUnit{
  private:
  TransUnitPtr plist;
  TransUnitPtr pdecl;

  protected:

public:
  ParamList(TransUnitPtr plist_, TransUnitPtr pdecl_): plist(plist_), pdecl(pdecl_){}

  virtual ~ParamList(){
    delete plist;
    delete pdecl;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    plist->PrettyPrint(dst);
    dst<<", ";
    pdecl->PrettyPrint(dst);
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      //todo
    }
};

#endif
