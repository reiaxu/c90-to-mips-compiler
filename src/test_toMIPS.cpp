#include "../include/ast.hpp"
#include "ast_transalationalunit.hpp"

int main()
{
    const TranslationalUnit *ast=parseAST();
    Bindings context = Bindings("main", 10);
    std::cout<<"Printing MIPS assembly"<<std::endl;
    ast->toMIPS(std::cout, " ", context);
    std::cout<<std::endl;

    return 0;
}
