#ifndef ast_typespec_hpp
#define ast_typespec_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class TypeSpec
      :public TranslationalUnit;

class TypeSpec{
  private:
    std::string type;

  protected:
    TypeSpec(const std::string &_type)
        :type(_type);
    {}

  public:
    void ~TypeSpec(){}

    virtual void PrettyPrint(std::ostream &dst) const override{
      dst<<type;
    }

};

#endif
