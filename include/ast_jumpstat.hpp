#ifndef ast_jumpstat_hpp
#define ast_jumpstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class JumpStat
      :public TranslationalUnit{
  private:
  std::string jump;
  TransUnitPtr primaryexpr=0;

  protected:

public:
  JumpStat(std::string _jump): jump(_jump){}
  JumpStat(std::string _jump, TransUnitPtr _primaryexpr)
  : jump(_jump)
  ,primaryexpr(_primaryexpr)
  {}

  virtual ~JumpStat(){
    delete primaryexpr;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(primaryexpr==0){
      dst<<jump<<';';
    }else{
      dst<<jump<<' ';
      primaryexpr->PrettyPrint(dst);
      dst<<';';
    }
  }
};

#endif
