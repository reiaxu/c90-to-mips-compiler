#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class Decl
    : public TranslationalUnit{

    private:
    TransUnitPtr dspec;
    TransUnitPtr dlist;

public:
    Decl(TransUnitPtr dspec_, TransUnitPtr dlist_):dspec(dspec_),dlist(dlist_){}

    ~Decl() override{
        delete dspec;
        delete dlist;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        if (dlist == NULL){
            dspec->PrettyPrint(dst);
            dst<<";";
            dst<<std::endl;
        }
        else {
            dspec->PrettyPrint(dst);
            dst<<" ";
            dlist->PrettyPrint(dst);
            dst<<";";
            dst<<std::endl;
        }

    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      if(dlist == NULL){
        //do nothing?
      }else{
        //decleration so its like we are creating the varaible for the first time
        //we must first insert the varaible into the binding
        dlist->toMIPS(dst, destReg, context);

      }
    }

};

#endif
