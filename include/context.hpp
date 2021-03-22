#ifndef context_hpp
#define context_hpp

//#include"ast_transalationalunit.hpp"

#include<string>
#include<vector>
#include <unordered_map>

//typedef const TranslationalUnit *TransUnitPtr;

struct type_pos{
  std::string type;
  int stack_offset;
};

class Bindings{
  private:
    int curr_stack_size = 0;
    std::string frame_id;
    int stack_frame;
    std::unordered_map< std::string,type_pos> var_bindings;

  public:
    Bindings(std::string frame, int stackaddr):frame_id(frame),stack_frame(stackaddr){}
    ~Bindings(){
      //free memory with type_pos.type?
    };

    void InsertBinding(const std::string _name,std::string _type){
      type_pos varinfo;
      curr_stack_size += 4;
      varinfo.type = _type;
      varinfo.stack_offset = curr_stack_size;
      var_bindings[_name] = varinfo;
    }

    const int getOffset(const std::string _name){
      return var_bindings[_name].stack_offset;
    }

    const int getNumVar(){
      return var_bindings.size();
    }

};

typedef struct var_param{

  std::string type;
  std::string name;

}param;

typedef std::vector<param> Params;

#endif
