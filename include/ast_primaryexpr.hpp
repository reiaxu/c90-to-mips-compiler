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
    TransUnitPtr expr;

  protected:

  public:
    PrimaryExpr(const std::string _type, std::string* _val)
    :type(_type),
    val(_val)
    {}

    PrimaryExpr(const std::string _type, TransUnitPtr _expr)
    :type(_type),
    expr(_expr)
    {}


    virtual ~PrimaryExpr(){
      delete val;
      delete expr;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
      if(type=="int"||type=="identif"){
        dst<<(*val);
      }
      else if(type=="expr"){
        dst<<"( ";
        expr->PrettyPrint(dst);
        dst<<") ";
      }
    }

};

#endif
