#ifndef ast_initializerlist_hpp
#define ast_initializerlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class InitList
    : public TranslationalUnit{
    
    private:
    TransUnitPtr list;
    TransUnitPtr init;

public:
    InitList(TransUnitPtr list_, TransUnitPtr init_):list(list_),init(init_){}

    ~InitList() override{
        delete list;
        delete init;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        
        list->PrettyPrint(dst);
        dst<<", ";
        init->PrettyPrint(dst);
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
        //todo
  }

};



#endif