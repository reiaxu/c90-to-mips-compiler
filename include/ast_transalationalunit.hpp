#ifndef ast_transalationalunit_hpp
#define ast_transalationalunit_hpp

#include<string>
#include<map>
#include<iostream>

#include "MIPSish.hpp"
#include"context.hpp"

class TranslationalUnit;

typedef const TranslationalUnit *TransUnitPtr;

class TranslationalUnit{
private:
  //TransUnitPtr tu=NULL;
  //TransUnitPtr ed=NULL;

public:
  //TranslationalUnit(TranslationalUnit * _tu, TranslationalUnit * _ed):tu(_tu), ed(_ed){}
  virtual ~TranslationalUnit()
  {
  //  delete tu;
    //delete ed;
  }

  virtual void PrettyPrint(std::ostream &dst) const = 0;
    //tu->PrettyPrint(dst);
    //ed->PrettyPrint(dst);
  

//  virtual void toMIPS(std::ostream &dst) const = 0;

//  virtual void toMIPS(std::ostream &dst, std::string destReg) const = 0;

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const = 0;
    //if(tu!=NULL) tu->toMIPS(dst, "$2", context);
    //if(ed!=NULL) ed->toMIPS(dst, "$2", context);

    //maybe make vector<Bindings> so that you can manage scopes better?
    //create new Bidning at the start of each function/scope, append then delete when done
};

#endif
