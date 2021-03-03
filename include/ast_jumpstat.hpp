#ifndef ast_jumpstat_hpp
#ifndef ast_jumpstat_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class JumpStat
      :public TranslationalUnit;

class JumpStat{
  private:
  std::string* jump;
  TransUnitPtr primaryexpr=NULLPTR;

  protected:
  JumpStat(std::string &_jump): jump(_jump){}
  JumpStat(std::string &_jump, TransUnitPtr _primaryexpr)
          : jump(_jump)
          ,primaryexpr(_primaryexpr)
  {}

public:
  virtual ~JumpStat(){
    delete primaryexpr;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    if(primaryexpr==NULLPTR){
      dst<<(*jump)<<';'
    }else{
      dst<<(*jump)<<' ';
      primaryexpr->PrettyPrint(dst);
      dst<<';';
    }
  }
};

#endif
