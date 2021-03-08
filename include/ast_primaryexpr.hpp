#ifndef ast_primaryexpr_hpp
#define ast_primaryexpr_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

class PrimaryExpr
      :public TranslationalUnit{
  private:
    std::string type;
    std::string* val;

  protected:

  public:
    PrimaryExpr(const std::string _type, std::string* _val)
    :type(_type),
    val(_val)
    {}

    virtual ~PrimaryExpr(){
      delete val;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      if(type=="int"||type=="identif"){
        dst<<(*val);
      }
    }

};

#endif
