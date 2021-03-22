#ifndef ast_jumpstat_hpp
#define ast_jumpstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

#include "context.hpp"
#include "MIPSish.hpp"

class JumpStat
      :public TranslationalUnit{
  private:
  std::string jump;
  TransUnitPtr expr = 0;

  protected:

public:
  JumpStat(std::string _jump): jump(_jump){}
  JumpStat(std::string _jump, TransUnitPtr _expr)
  : jump(_jump)
  ,expr(_expr)
  {}

  virtual ~JumpStat(){
    delete expr;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(expr==0){
      dst<<jump<<"; ";
    }else{
      dst<<jump<<" ";
      expr->PrettyPrint(dst);
      dst<<"; ";
    }
  }

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
    if(expr==0){
      if(jump=="return"){
        o_nop(dst);
      }
    }else{
      std::string destReg = "$2";
      expr->toMIPS(dst,destReg, context);
    }
  }

};

#endif
