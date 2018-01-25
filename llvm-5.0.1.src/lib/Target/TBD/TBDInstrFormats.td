//===-- TBDInstrInfo.td - TBD Instruction Formats ----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// TBD Instruction Format Definitions.
//
//===----------------------------------------------------------------------===//

// A generic TBD instruction.
class TBDInst<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction
{
  let Namespace = "TBD";

  dag OutOperandList  = outs    ;
  dag InOperandList   = ins     ;
  let AsmString       = asmstr  ;
  let Pattern         = pattern ;

  field bits<32> Inst     ;
  field bits<32> SoftFails;  // Mask bits for reservied fieldsFails;  // Mask bits for reservied fields
  let   Size = 4          ;  // The instruction in bytes  
}


//===----------------------------------------------------------------------===//
//R-type instruction 
// 31-25  24-20  19-15  14-12   11-7  6-0
// funct7  rs2   rs1    funct3  rd    opcode 
//===----------------------------------------------------------------------===//
// dag outs:  Input register list.  GPR is the defined register class in TBDRegsiterInfo.td 
// dag ins :  Input register list.  GPR is the defined register class in TBDRegsiterInfo.td 
// list<dag> pattern: the pattern selectin for compiler? we leave it blank right now.
// asmstr  :  assembler string. Why there is ! mark before the strconcat()?
class RInst<bits<7> funct7, bits<3> funct3, bits<7> opcode, string op_str, list<dag> pattern=[] > 
    : TBDInst < (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2), !strconcat( op_str, "\t$rd, $rs1, $rs2"), pattern >
{
  bits<5> rs2 ;
  bits<5> rs1 ;
  bits<5> rd  ;

  let Inst{31-25} = funct7  ;
  let Inst{24-20} = rs2     ;
  let Inst{19-15} = rs1     ;
  let Inst{14-12} = funct3  ;
  let Inst{11- 7} = rd      ;
  let Inst{6 - 0} = opcode  ;
}

