//===-- TBDInstrInfo.td - TBD Instruction defs -------------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the TBD instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "TBDInstrFormats.td"

// RInst<bits<7> funct7, bits<3> funct3, bits<7> opcode, string op_str, list<dag> pattern=[] > 
def ADD: RInst<0b0000000, 0b000, 0b0110011, "ADD">; 
