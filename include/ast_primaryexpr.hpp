#ifndef ast_primaryexpr_hpp
#define ast_primaryexpr_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>

#include "context.hpp"
#include "MIPSish.hpp"


class PrimaryExpr
      :public TranslationalUnit{
  private:
    std::string type;
    const std::string* val;

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

    /*const std::string getType(){
      return type;
    }*/

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
      if(type=="int"){
        o_li(dst, destReg, *(val));
      }else if(type=="indentif"){
        std::string offset = std::to_string(context.getOffset(*val));
        o_lw(dst, destReg, offset,"$fp");
        o_nop(dst);
      }
    }

};

#endif
