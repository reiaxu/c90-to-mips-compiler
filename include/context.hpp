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

typedef std::vector<std::string> Params;

class Bindings{
  private:
    std::string scopeName;
    int curr_stack_size = 8; //stack size wrt $fp
    int stack_frame; //value of $fp?
    std::unordered_map< std::string,int> var_bindings; //bindings of all vars and their offsets wrt to $fp (value of stack pos when they were pushed)
    Params func_args;
    int num_of_args=0;

  public:
    Bindings(std::string _scopeName):scopeName(_scopeName){};
    ~Bindings(){
      //free memory with type_pos.type?
    };

    void insertBinding(const std::string _name/*,std::string _type*/){

      if(var_bindings.find("_name") != var_bindings.end()){
        //updateBinding(_name); --> just have it check if it is in, store value in temp then just use that in the same way but ya
        //is this even needed?
      }else{
        //type_pos varinfo;
        //varinfo.type = _type;
        //varinfo.stack_offset = curr_stack_size;
        //var_bindings[_name] = curr_stack_size;
        var_bindings.insert(std::make_pair(_name,curr_stack_size));
        curr_stack_size += 4;
      }
   }

    void insertArrayBinding(const std::string _name, int _sizeofarray){
      var_bindings.insert(std::make_pair(_name,curr_stack_size));
      curr_stack_size += (4*_sizeofarray);
    }

    int getOffset(const std::string _name){
      int off = var_bindings[_name];
      return off;
    }

    int getNumVar(){
      return var_bindings.size();
    }

    void insertArgBinding(const std::string _name){
      num_of_args++;
      func_args.push_back(_name);
    }

    int getAllArgNum(){
      return num_of_args;
    }

    /*int getArgNum(const std::string _name){
      auto it = find(func_args.begin(), func_args.end(), _name);
      // found
      if (it != func_args.end()){
          // calculating the index
          int index = it - func_args.begin();
          return index;
      }else{
          //not in list?
          return -1;
      }
    }*/

    void printContext(std::ostream &dst){
      for(const auto& x : var_bindings) {
        dst<<x.first << ": " << x.second << "\n";
      }
    }

    std::string getScopeName()
    {
        return scopeName;
    }

};

/*typedef struct var_param{

  std::string type;
  std::string name;

}param;*/

#endif
