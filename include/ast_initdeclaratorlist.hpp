#ifndef ast_initdeclaratorlist_hpp
#define ast_initdeclaratorlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class InitDeclList
    : public TranslationalUnit{

    private:
    TransUnitPtr list;
    TransUnitPtr decl;

public:
    InitDeclList(TransUnitPtr list_, TransUnitPtr decl_):list(list_),decl(decl_){}

    ~InitDeclList() override{
        delete list;
        delete decl;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{

        list->PrettyPrint(dst);
        dst<<", ";
        decl->PrettyPrint(dst);
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      list->toMIPS(dst, destReg, context);
      decl->toMIPS(dst, destReg, context);
    }

};



#endif
