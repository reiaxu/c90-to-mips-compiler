#ifndef context_hpp
#define context_hpp

//#include"ast_transalationalunit.hpp"

#include<string>
#include<vector>
#include <unordered_map>
#include<iostream>

//typedef const TranslationalUnit *TransUnitPtr;

struct type_pos{
  //std::string type;
  int stack_offset;
};

class Bindings{
  private:
    int curr_stack_size = 8; //stack size wrt $fp
    int stack_frame; //value of $fp?
    std::unordered_map< std::string,int> var_bindings; //bindings of all vars and their offsets wrt to $fp (value of stack pos when they were pushed)

  public:
    Bindings(){};
    ~Bindings(){
      //free memory with type_pos.type?
    };

    void insertBinding(const std::string _name/*,std::string _type*/){
      if(var_bindings.find("_name") != var_bindings.end()){
        //updateBinding(_name);
      }else{
        //type_pos varinfo;
        //varinfo.type = _type;
        //varinfo.stack_offset = curr_stack_size;
        var_bindings[_name] = curr_stack_size;
        curr_stack_size += 4;
      }
   }

    int getOffset(const std::string _name){
      int off = var_bindings[_name];
      return off;
    }

   int getNumVar(){
      return var_bindings.size();
    }

    void printContext(std::ostream &dst){
      for(const auto& x : var_bindings) {
        dst<<x.first << ": " << x.second << "\n";
      }
    }

};

typedef struct var_param{

  std::string type;
  std::string name;

}param;

typedef std::vector<param> Params;

#endif
