#include "../include/ast.hpp"
//#include "c_parser.tab.hpp"

int main()
{
    const TranslationalUnit *ast=parseAST();

    ast->PrettyPrint(std::cout);
    std::cout<<std::endl;

    return 0;
}
