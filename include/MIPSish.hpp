#ifndef mipsish_hpp
#define mipsish_hpp

#include<iostream>
#include <string>

inline void genL(std::ostream &dst, std::string label){
  dst<<label<<':'<<std::endl;
}

inline void o_nop(std::ostream &dst){
  dst<<"nop"<<std::endl;
}

inline void o_li(std::ostream &dst, std::string dReg,std::string imm){
    dst<<"li "+dReg+','+imm<<std::endl;
}

inline void o_move(std::ostream &dst, std::string dReg,std::string sReg){
    dst<<"move "+dReg+','+sReg<<std::endl;
}

inline void o_lw(std::ostream &dst,std::string dReg,std::string offset,std::string sReg){
    dst<<"lw "+dReg+','+offset+'('+sReg+')'<<std::endl;
}

inline void o_sw(std::ostream &dst, std::string dReg,std::string offset,std::string sReg){
    dst<<"sw "+dReg+','+offset+'('+sReg+')'<<std::endl;
}

inline void o_add(std::ostream &dst, std::string dReg,std::string sReg,std::string s2Reg){
    dst<<"add "+dReg+','+sReg+','+s2Reg<<std::endl;
}

inline void o_addi(std::ostream &dst, std::string tReg,std::string sReg,std::string imm){
    //chyk il ashya2 mal addr
    dst<<"addi "+tReg+','+sReg+','+imm<<std::endl;
}

inline void o_addiu(std::ostream &dst, std::string tReg,std::string sReg,std::string imm){
    dst<<"addiu "+tReg+','+sReg+','+imm<<std::endl;
}

inline void o_addu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"addu "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_and(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"and "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_andi(std::ostream &dst, std::string tReg,std::string sReg,std::string imm){
    dst<<"andi " +tReg+','+sReg+','+imm<<std::endl;
}

inline void o_b(std::ostream &dst, std::string label){
    dst<<"b "+label<<std::endl;
}

inline void o_mul(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"mult "+sReg+','+tReg<<std::endl;
    dst<<"mflo "+dReg<<std::endl;
}

inline void o_div(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"div "+sReg+','+tReg<<std::endl;
    dst<<"mflo "+dReg<<std::endl;
}

inline void o_divu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"divu "+sReg+','+tReg<<std::endl;
    dst<<"mflo "+dReg<<std::endl;
}

inline void o_modu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"div "+sReg+','+tReg<<std::endl;
    dst<<"mfhi "+dReg<<std::endl;
}

inline void o_umodu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"divu "+sReg+','+tReg<<std::endl;
    dst<<"mfhi "+dReg<<std::endl;
}

inline void o_sub(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sub "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_subu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"subu "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_sll(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sll "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_srl(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"srl "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_sla(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sra "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_sra(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sra "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_sltiu(std::ostream &dst, std::string dReg,std::string sReg,std::string imm){
    dst<<"sltiu "+dReg+','+sReg+','+imm<<std::endl;
}

inline void o_sltu(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sltu "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_slt(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"slt "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_goe(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){

}

inline void o_loe(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"slt "+dReg+','+tReg+','+sReg<<std::endl;
    dst<<"xori "+dReg+','+dReg+','+'1'<<std::endl;
}

inline void o_eq(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"sub "+dReg+','+sReg+','+tReg<<std::endl;
    dst<<"slt"+dReg+','+dReg+','+"$0"<<std::endl;
}

inline void o_neq(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"xor "+dReg+','+sReg+','+tReg<<std::endl;
    dst<<"slt "+dReg+','+"$0"+','+dReg<<std::endl;
}

inline void o_xor(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"xor "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_or(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"or "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_nor(std::ostream &dst, std::string dReg,std::string sReg,std::string tReg){
    dst<<"nor "+dReg+','+sReg+','+tReg<<std::endl;
}

inline void o_jal(std::ostream &dst, std::string label){
    dst<<"jal "+label<<std::endl;
}

inline void o_jr(std::ostream &dst, std::string dReg){
    dst<<"jr "+dReg<<std::endl;
}

inline void o_beq(std::ostream &dst, std::string sReg,std::string tReg,std::string label){
    dst<<"beq "+sReg+','+tReg+','+label<<std::endl;
}

inline void o_bne(std::ostream &dst, std::string sReg,std::string tReg, std::string label){
    dst<<"bne "+sReg+','+tReg+','+label<<std::endl;
}

#endif
