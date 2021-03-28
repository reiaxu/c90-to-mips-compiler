#ifndef ast_declarationlist_hpp
#define ast_declarationlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class DeclList
    : public TranslationalUnit{
    
    private:
    TransUnitPtr dlist;
    TransUnitPtr decl;

public:
    DeclList(TransUnitPtr dlist_, TransUnitPtr decl_):dlist(dlist_),decl(decl_){}

    ~DeclList() override{
        delete dlist;
        delete decl;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        dlist->PrettyPrint(dst);
        dst<<" ";
        decl->PrettyPrint(dst);

    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      //todo
    }

};



#endif