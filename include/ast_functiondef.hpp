#ifndef ast_functiondef_hpp
#define ast_functiondef_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class FunctionDef
      :public TranslationalUnit{

  private:
    TransUnitPtr type;
    std::string* identif;
    TransUnitPtr jumpstat;

  protected:

  public:
   FunctionDef(TransUnitPtr _type,
      std::string* _identif,
      TransUnitPtr _jumpstat)

      :type(_type)
      ,identif(_identif)
      ,jumpstat(_jumpstat)
      {}

    virtual ~FunctionDef(){
      delete type;
      delete identif;
      delete jumpstat;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      if (type==NULL) {
        dst<<(*identif)<<" ";
        jumpstat->PrettyPrint(dst);
      }
      else {
        type->PrettyPrint(dst);
        dst<<" "<<(*identif)<<" ";
        jumpstat->PrettyPrint(dst);
      }
    }


};

//typedef FunctionDef* FuncDefPtr;

#endif
