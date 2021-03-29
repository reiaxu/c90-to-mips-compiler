#ifndef ast_enumspecifier_hpp
#define ast_enumspecifier_hpp

#include"ast_transalationalunit.hpp"
#include "context.hpp"

#include<string>
#include<map>
#include<iostream>

class EnumSpec
      :public TranslationalUnit{
  private:
    std::string *identif;
    TransUnitPtr list;

  protected:

  public:
    EnumSpec(std::string* identif_, TransUnitPtr list_):identif(identif_), list(list_)
    {}

    virtual ~EnumSpec(){
        delete list;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      dst<<"enum ";
      if (list == NULL && identif != NULL){
          dst<<(*identif);
      }
      else if (identif==NULL && list != NULL){
          dst<<"{";
          list->PrettyPrint(dst);
          dst<<"} ";
      }
      else if (list != NULL && identif != NULL){
          dst<<(*identif)<<" {";
          list->PrettyPrint(dst);
          dst<<"} ";
      }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
        //notsure, probably do nothing?
    }

};

#endif
