#ifndef ast_initdeclarator_hpp
#define ast_initdeclarator_hpp

#include"ast_transalationalunit.hpp"
#include"ast_directdecl.hpp"
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
      if(init!=NULL){
        std::string temp = "$t0";
        //evaluate init, store in destReg
        init->toMIPS(dst, temp, context);
        //get name of var and its offset
        DirectDecl *_casted = (DirectDecl*) decl;
        std::string var_name = _casted->getName();
        context->insertBinding(var_name);
        std::string _offset = std::to_string(context->getOffset(var_name));
        //load temp into memaddr of decl
        o_sw(dst, temp, _offset, "$fp");

      }std::string temp = "$t0";
      //evaluate init, store in destReg
      //get name of var and its offset

      DirectDecl *_casted = (DirectDecl*) decl;
      std::string var_name = _casted->getName();
      context->insertBinding(var_name);
    }

};



#endif
