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
    FunctionDef(TransUnitPtr _type,
                std::string* _identif,
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
      dst<<" "<<(*identif)<<"(){\n";
      jumpstat->PrettyPrint(dst);
      dst<<"\n }";
    }


};

//typedef FunctionDef* FuncDefPtr;

#endif
