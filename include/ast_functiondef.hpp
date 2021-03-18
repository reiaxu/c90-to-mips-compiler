#ifndef ast_functiondef_hpp
#define ast_functiondef_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class FunctionDef
      :public TranslationalUnit{

  private:
    TransUnitPtr decspec;
    std::string* declarator;
    TransUnitPtr compoundstat;

  protected:

  public:
   FunctionDef(TransUnitPtr _decspec,
      std::string* _declarator,
      TransUnitPtr _compoundstat)

      :decspec(_decspec)
      ,declarator(_declarator)
      ,compoundstat(_compoundstat)
      {}

    virtual ~FunctionDef(){
      delete decspec;
      delete declarator;
      delete compoundstat;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      decspec->PrettyPrint(dst);
      dst<<" "<<(*declarator)<<"(){";
      dst<<std::endl;
      compoundstat->PrettyPrint(dst);
      dst<<std::endl;
      dst<<"}";
    }

    virtual void toMIPS(std::ostream &dst) const override{
      dst<<*declarator<<":"<<std::endl;
      compoundstat->toMIPS(dst);
      dst<<"j $31"<<std::endl;
      dst<<"nop"<<std::endl;

    }

};


#endif
