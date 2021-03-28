#ifndef ast_typespec_hpp
#define ast_typespec_hpp

#include"ast_transalationalunit.hpp"
#include "context.hpp"

#include<string>
#include<map>
#include<iostream>

class TypeSpec
      :public TranslationalUnit{
  private:
    std::string type;

  protected:

  public:
    TypeSpec(const std::string &_type)
    :type(_type)
    {}

    virtual ~TypeSpec(){}

    virtual void PrettyPrint(std::ostream &dst) const override{
      dst<<type;
    }

    std::string getType(){
      return type;
    }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings* context) const override{
        //notsure, probably do nothing?
    }

};

#endif
