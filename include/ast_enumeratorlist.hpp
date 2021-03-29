#ifndef ast_enumeratorlist_hpp
#define ast_enumeratorlist_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class EnumeratorList
    : public TranslationalUnit{

    private:
    TransUnitPtr list;
    TransUnitPtr en;

public:
    EnumeratorList(TransUnitPtr list_, TransUnitPtr en_):list(list_),en(en_){}

    ~EnumeratorList() override{
        delete list;
        delete en;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{

        list->PrettyPrint(dst);
        dst<<", ";
        en->PrettyPrint(dst);
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
        
        list->toMIPS(dst, "$5", context);
        en->toMIPS(dst, "$4", context);
  }

};



#endif
