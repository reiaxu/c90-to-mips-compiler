#ifndef ast_directdecl_hpp
#define ast_directdecl_hpp

#include"ast_transalationalunit.hpp"

#include<string>
#include<map>
#include<iostream>


class DirectDecl
    : public TranslationalUnit{
    
    private:
    const int type;
    std::string* identif;
    TransUnitPtr decl; 
    TransUnitPtr list;

public:
    DirectDecl(const int type_, std::string* identif_):type(type_),identif(identif_){}
    DirectDecl(const int type_, TransUnitPtr decl_):type(type_),decl(decl_){}
    DirectDecl(const int type_, TransUnitPtr decl_, TransUnitPtr list_):type(type_),decl(decl_), list(list_){}

    virtual ~DirectDecl() {
        delete identif;
        delete decl;
        delete list;
    }

    virtual void PrettyPrint(std::ostream &dst) const override{
        if (type==0) {
            dst<<(*identif);
        }
        else if (type==1) {
            decl->PrettyPrint(dst);
            dst<<" ()";
        }
        else if (type==2) {
            dst<<"(";
            decl->PrettyPrint(dst);
            dst<<")";
        }
        else if (type==3) {
            decl->PrettyPrint(dst);
            dst<<" [";
            list->PrettyPrint(dst);
            dst<<"]";
        }
        else if (type==4) {
            decl->PrettyPrint(dst);
            dst<<" []";
        }
        else if (type==5){
            decl->PrettyPrint(dst);
            dst<<" (";
            list->PrettyPrint(dst);
            dst<<")";
        }
    }

    // std::string getName(){
    //     if(type==0){
    //         return (*identif);
    //     }else{
    //         dd->getName();
    //     }
    // }

    virtual void toMIPS(std::ostream &dst, std::string destReg, Bindings context) const override{
        //todo
  }

};



#endif