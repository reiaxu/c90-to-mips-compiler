#ifndef ast_functiondef_hpp
#define ast_functiondef_hpp

#include"ast_transalationalunit.hpp"
#include "MIPSish.hpp"
#include "context.hpp"

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
      if (decspec==NULL) {
        dst<<(*declarator)<<" ";
        compoundstat->PrettyPrint(dst);
      }
      else {
        decspec->PrettyPrint(dst);
        dst<<" "<<(*declarator)<<" ";
        compoundstat->PrettyPrint(dst);
      }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      //genL(dst, *declarator);
      //prior to func execution, store return addr, store args to func,
      //o_addiu(dst, "$sp", "$sp", "OFFSET?");
      //o_sw(dst,"$fp","OFFSET?","$sp");
      //o_move(dst, "$fp", "$sp");
      //compoundstat->toMIPS(dst, destReg, context);
      //o_move(dst, "$sp", "$fp");
      //o_lw(dst, "$fp", "OFFSET?", "$sp");
      //o_addiu(dst, "$sp", "$sp", "OFFSET?");
      //make sure to get $ra off stack!
      //o_jr(dst,"$31");
      //o_nop(dst);

    }

};


#endif
