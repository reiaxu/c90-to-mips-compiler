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

public:
  virtual ~TranslationalUnit()
  {}

  virtual void PrettyPrint(std::ostream &dst) const = 0;

//  virtual void toMIPS(std::ostream &dst) const = 0;

//  virtual void toMIPS(std::ostream &dst, std::string destReg) const = 0;

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const = 0;
    //maybe make vector<Bindings> so that you can manage scopes better?
    //create new Bidning at the start of each function/scope, append then delete when done
};

#endif
