#include "c_lexparse.hpp"

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

TokenVal yylval;

int main(){
  std::cout<<"Enter program to be tokenized:"<<std::endl;
  while(1){
    
    TokenType type=(TokenType)yylex();

    if(type == IDENTIFIER){
      std::cout<<"Token seen is: IDENTIFIER"<<std::endl;

    }else if( type == CONSTANT ){
      std::cout<<"Token seen is: NUMCONST"<<std::endl;

    }else if( type == INT){
      std::cout<<"Token seen is: INT TYPE"<<std::endl;

    }else if( type == RETURN){
      std::cout<<"Token seen is: RETURN"<<std::endl;

    }else if((int)type < 256){
      std::cout<<"Token seen is: "<<char(type)<<std::endl;

    }else{
      return 1;

    }
  }
}
