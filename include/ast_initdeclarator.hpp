#ifndef ast_initdeclarator_hpp
#define ast_initdeclarator_hpp

#include"ast_transalationalunit.hpp"
#include"ast_directdecl.hpp"
#include"ast_primaryexpr.hpp"

#include"context.hpp"

#include<string>
#include<map>
#include<iostream>


class InitDecl
    : public TranslationalUnit{

    private:
    TransUnitPtr decl;
    TransUnitPtr init;

public:
    InitDecl(TransUnitPtr decl_, TransUnitPtr init_):decl(decl_),init(init_){}

    virtual ~InitDecl() {
        delete decl;
        delete init;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        if (init==NULL) {
            decl->PrettyPrint(dst);
        }
        else {
            decl->PrettyPrint(dst);
            dst<<" = ";
            init->PrettyPrint(dst);
        }
    }


    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      //get name of var and inser to binding
      DirectDecl *_casted = (DirectDecl*) decl;
      std::string var_name = _casted->getName();
      int dd_type = _casted->getType();
        if(dd_type==0||dd_type==2){
          context->insertBinding(var_name);
        }else if(dd_type==3){
          TransUnitPtr cexpr = _casted->getConstExpr();
          PrimaryExpr* pexpr = (PrimaryExpr*) cexpr;
          std::string _arrsize = pexpr->getName();
          context->insertArrayBinding(var_name, stoi(_arrsize));
        }
      if(init!=NULL){

        std::string temp = "$t0";
        init->toMIPS(dst, temp, context);

        if(dd_type==0||dd_type==2){
          //evaluate init, store in destReg
          //get var offset
          std::string _offset = std::to_string(context->getOffset(var_name));
          //load temp into memaddr of decl
          o_addiu(dst, "$sp", "$sp", "-4");
          o_sw(dst, temp, _offset, "$fp");
        }else if(dd_type==3){
        //  std::string _offset = std::to_string(context->getOffset(var_name));
        // i dont think this is tested
        }

      }else{
        //idk atm
      }
    }

};



#endif
