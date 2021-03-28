#include<iostream>
#include <fstream>

#include "ast.hpp"
#include "context.hpp"
#include "ast_transalationalunit.hpp"

FILE* input_file;
std::ofstream output_file;

int main(int argc, char* argv[])
{
		if(argc!=5){
			std::cerr<<"Incorrect number of arguments specified for program"<<std::endl;
		}else{
			//setting I/O files
			input_file=fopen(argv[2],"r");
			output_file.open(argv[4]);
			//Lex and parse to build AST
			const TranslationalUnit *ast=parseAST(input_file);
			//start codeGen
	    Bindings context = Bindings("main");
	    ast->toMIPS(output_file, " ", context);

			fclose(input_file);
			output_file.close();
			delete ast;

	     return 0;
		}
}

/*
int main()
{
	std::cout << "f:" << std::endl;
	std::cout << "PUSH0:" << std::endl;
	std::cout << "addiu $sp, $sp, -44" << std::endl;
	std::cout << "sw $ra, 40($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $fp, 36($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s0, 4($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s1, 8($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s2, 12($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s3, 16($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s4, 20($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s5, 24($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s6, 28($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "sw $s7, 32($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "body2:" << std::endl;
	std::cout << "li $v0, 42" << std::endl;
	std::cout << "addiu $sp, $sp, 0" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "b POP1" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "addiu $sp, $sp, 0" << std::endl;
	std::cout << "move $fp, $sp" << std::endl;
	std::cout << "POP1:" << std::endl;
	std::cout << "mtc1 $v0, $f0" << std::endl;
	std::cout << "lw $s0, 4($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s1, 8($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s2, 12($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s3, 16($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s4, 20($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s5, 24($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s6, 28($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $s7, 32($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $ra, 40($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "lw $fp, 36($sp)" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << "move $sp, $fp" << std::endl;
	std::cout << "jr $ra" << std::endl;
	std::cout << "nop" << std::endl;
	std::cout << ".global f" << std::endl;
}
*/
