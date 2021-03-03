#ifndef ast_transalationalunit_hpp
#define ast_transalationalunit_hpp

#include<string>
#include<map>
#include<iostream>

class TranslationalUnit;

typedef const TranslationalUnit* TransUnitPtr;

class TranslationalUnit{

public:
  virtual ~TranslationalUnit()
  {}

  virtual void PrettyPrint(std::ostream &dst) const = 0;


};

#endif
