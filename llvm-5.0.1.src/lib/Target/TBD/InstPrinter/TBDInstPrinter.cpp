//===-- TBDInstPrinter.cpp - Convert TBD MCInst to assembly syntax --===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an TBD MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "TBDInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#include "TBDGenAsmWriter.inc"

//===----------------------------------------------------------------------===//
// printInst
void TBDInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                                  StringRef Annot, const MCSubtargetInfo &STI) {
  //This function is automatically generated by Tablegen
  printInstruction(MI, O);
}

//===----------------------------------------------------------------------===//
// printOperand
void TBDInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O, 
					const char *Modifier ){
  const MCOperand &Op = MI->getOperand(OpNo);
  //Now we only supports register operands.
  if (Op.isReg())     	O << getRegisterName(Op.getReg());  
  else 			assert( "unknown operand kind in printOperand");
}
