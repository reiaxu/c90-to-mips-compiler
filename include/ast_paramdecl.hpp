#ifndef ast_paramdecl_hpp
#define ast_paramdecl_hpp

#include"ast_transalationalunit.hpp"
#include"ast_directdecl.hpp"


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

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
    DirectDecl *_casted = (DirectDecl*) decl;
    std::string arg_name = _casted->getName();
    context->insertBinding(arg_name);
    context->insertArgBinding(arg_name);
    std::string _offset = std::to_string(context->getOffset(arg_name));
    //if(destReg==" ") destReg="$4";
    int argRank = context->getAllArgNum();
    if(argRank==1){
      o_sw(dst, "$4", _offset, "$fp");
    }else if(argRank==2){
      o_sw(dst, "$5", _offset, "$fp");
    }else if(argRank==3){
      o_sw(dst, "$6", _offset, "$fp");
    }else if(argRank==4){
      o_sw(dst, "$7", _offset, "$fp");
    }
  }
};

#endif
