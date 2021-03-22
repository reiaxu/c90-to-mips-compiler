#ifndef ast_paramdecl_hpp
#define ast_paramdecl_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class ParamDecl
      :public TranslationalUnit{
  private:
  TransUnitPtr decspec;
  TransUnitPtr decl;

  protected:

public:
  ParamDecl(TransUnitPtr decspec_, TransUnitPtr decl_): decspec(decspec_), decl(decl_){}

  virtual ~ParamDecl(){
    delete decspec;
    delete decl;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if (decl==NULL){
        decspec->PrettyPrint(dst);
    }
    else {
        decspec->PrettyPrint(dst);
        dst<<" ";
        decl->PrettyPrint(dst);
    }
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      //todo
    }
};

#endif
