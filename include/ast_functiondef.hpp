#ifndef ast_functiondef_hpp
#define ast_functiondef_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class FunctionDef
      :public TranslationalUnit;

typedef FunctionDef* FuncDefPtr;

class FunctionDef{

  private:
    TransUnitPtr type;
    TransUnitPtr identif;
    TransUnitPtr jumpstat;

  protected:
    FunctionDef(TransUnitPtr _type,
                TransUnitPtr _identif,
                TransUnitPtr _jumpstat)

              :type(_type)
              ,identif(_identif)
              ,jumpstat(_jumpstat)
    {}

  public:
    virtual ~FunctionDef(){
      delete type;
      delete identif;
      delete jumpstat;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      type->PrettyPrint(dst);
      dst<<" ";
      identif->PrettyPrint(dst);
      dst<<"(){\n";
      jumpstat->PrettyPrint(dst);
      dst<<"\n }";
    }


};

#endif
