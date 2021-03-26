#include "../include/ast.hpp"
#include "ast_transalationalunit.hpp"

int main()
{
    const TranslationalUnit *ast=parseAST(NULL);
    Bindings context = Bindings();
    std::cout<<"Printing MIPS assembly"<<std::endl;
    ast->toMIPS(std::cout, " ", context);
    std::cout<<std::endl;

    delete ast;

    return 0;
}
