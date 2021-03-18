#ifndef context_hpp
#define context_hpp

#include<string>
#include<vector>
#include <unordered_map>
#include "ast.hpp"

struct type_pos{
  TransUnitPtr type;
  int stack_offset;
};

class Bindings{
  private:
    std::string frame_id;
    int stack_frame;
    std::unordered_map< std::string,type_pos> var_bindings;

  public:
    Bindings();
    ~Bindings(){
      //free memory with type_pos.type?
    };

    void InsertBinding(const std::string _name,TransUnitPtr _type, int _stackpos){
      type_pos varinfo;
      varinfo.type = _type;
      varinfo.stack_offset = _stackpos;
      var_bindings[_name] = varinfo;
    }

};

typedef struct var_param{

  TransUnitPtr type;
  std::string name;

}param;

typedef std::vector<param> Params;

#endif
