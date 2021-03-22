#ifndef ast_initdeclarator_hpp
#define ast_initdeclarator_hpp

#include"ast_transalationalunit.hpp"

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


    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
        //todo
  }

};



#endif