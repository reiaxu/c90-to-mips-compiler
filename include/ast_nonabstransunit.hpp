#ifndef ast_nonabstransunit_hpp
#define ast_nonabstransunit_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

#include "MIPSish.hpp"
#include"context.hpp"


class nonABSTransUnit: public TranslationalUnit{
private:
  TransUnitPtr tu=NULL;
  TransUnitPtr ed=NULL;

public:
  nonABSTransUnit(TransUnitPtr _tu, TransUnitPtr _ed):tu(_tu), ed(_ed){}
  virtual ~nonABSTransUnit()
  {
    delete tu;
    delete ed;
  }

  virtual void PrettyPrint(std::ostream &dst) const override{
    tu->PrettyPrint(dst);
    ed->PrettyPrint(dst);
  }


//   virtual void toMIPS(std::ostream &dst) const = 0;

//  virtual void toMIPS(std::ostream &dst, std::string destReg) const = 0;

  virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
    if(tu!=NULL) tu->toMIPS(dst, "$2", context);
    if(ed!=NULL) ed->toMIPS(dst, "$2", context);

    //maybe make vector<Bindings> so that you can manage scopes better?
    //create new Bidning at the start of each function/scope, append then delete when done
  }
};

#endif
