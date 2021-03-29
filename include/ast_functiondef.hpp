#ifndef ast_functiondef_hpp
#define ast_functiondef_hpp

#include"ast_transalationalunit.hpp"
#include"ast_directdecl.hpp"
#include "MIPSish.hpp"
#include "context.hpp"

#include<string>
#include<map>
#include<iostream>

class FunctionDef
      :public TranslationalUnit{

  private:
    TransUnitPtr decspec;
    TransUnitPtr declarator;
    TransUnitPtr compoundstat;

  protected:

  public:
   FunctionDef(TransUnitPtr _decspec,
      TransUnitPtr _declarator,
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
        declarator->PrettyPrint(dst);
        dst<<" ";
        compoundstat->PrettyPrint(dst);
      }
      else {
        decspec->PrettyPrint(dst);
        dst<<" ";
        declarator->PrettyPrint(dst);
        dst<<" ";
        compoundstat->PrettyPrint(dst);
      }
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
      //prior to func execution, store return addr, store args to func
      //DirectDecl* decl = (DirectDecl*) declarator;
      //declarator->toMIPS(dst, "LABEL", context);
      //const DirectDecl *_casted = dynamic_cast<DirectDecl*>(declarator);
      DirectDecl *_casted = (DirectDecl*) declarator;
      dst<<".text"<<std::endl;
      dst<<".globl "<<_casted->getName()<<std::endl;
      genL(dst,_casted->getName());
      o_addiu(dst, "$sp", "$sp", "-8");
      o_sw(dst,"$fp","0","$sp");
      o_sw(dst,"$ra","4","$sp");
      //declarator->toMIPS(dst, destReg, context);
      //o_sw(dst,"$fp","OFFSET?","$sp");
      o_move(dst, "$fp", "$sp");
      Bindings* funccontext = new Bindings(_casted->getName());
      compoundstat->toMIPS(dst, "$2", funccontext);
      o_move(dst, "$sp", "$fp");
      //o_lw(dst, "$fp", "OFFSET?", "$sp");
      //make sure to get $ra and $fp off stack!
      o_lw(dst, "$fp", "0", "$sp");
      o_lw(dst, "$ra", "4", "$sp");
      o_addiu(dst, "$sp", "$sp", "8");
      o_jr(dst,"$ra");
      o_nop(dst);

    }

};


#endif
