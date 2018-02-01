//===- TBDDisassembler.cpp - Disassembler for TBD ---------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is part of the TBD Disassembler.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TBDMCTargetDesc.h"

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "avr-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

namespace {

/// A disassembler class for TBD.
class TBDDisassembler : public MCDisassembler {
public:
  TBDDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}
  virtual ~TBDDisassembler() {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &VStream,
                              raw_ostream &CStream) const override;
};
}

static MCDisassembler *createTBDDisassembler(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             MCContext &Ctx) {
  return new TBDDisassembler(STI, Ctx);
}


extern "C" void LLVMInitializeTBDDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheTBDTarget(),
                                         createTBDDisassembler);
}

//===----------------------------------------------------------------------===//
//  Decode the registers
//===----------------------------------------------------------------------===//
static unsigned
getTBDRegister(const void *D, unsigned RC, unsigned RegNo) {
        const TBDDisassembler *Dis 	= static_cast<const TBDDisassembler*>(D);
  	const MCRegisterInfo *RegInfo 	= Dis->getContext().getRegisterInfo();
  	return *(RegInfo->getRegClass(RC).begin() + RegNo);
}

static DecodeStatus DecodeGPRRegisterClass(MCInst &Inst, unsigned RegNo,
                                            uint64_t Address, const void *Decoder) {
  //The TBDReg::GPRRegClassID is generated in TBDGenRegisterInfo.inc 
  unsigned RegInd = getTBDRegister(Decoder, TBDReg::GPRRegClassID, RegNo); 
  Inst.addOperand( MCOperand::createReg( RegInd ) );

  return MCDisassembler::Success;
}

#include "TBDGenDisassemblerTables.inc"

static DecodeStatus readInstruction32(ArrayRef<uint8_t> Bytes, uint64_t Address,
                                      uint64_t &Size, uint32_t &Insn) {

  if (Bytes.size() < 4) {
    Size = 0;
    return MCDisassembler::Fail;
  }

  Size = 4;
  Insn = (Bytes[0] << 0) | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

  return MCDisassembler::Success;
}

static const uint8_t *getDecoderTable(uint64_t Size) {

  switch (Size) {
    case 4: return DecoderTable32;
    default: llvm_unreachable("instructions must be 32-bits");
  }
}

DecodeStatus TBDDisassembler::getInstruction(MCInst &Instr, uint64_t &Size,
                                             ArrayRef<uint8_t> Bytes,
                                             uint64_t Address,
                                             raw_ostream &VStream,
                                             raw_ostream &CStream) const {
  uint32_t Insn;

  DecodeStatus Result;

  // Try decode a 32-bit instruction.
  {
    Result = readInstruction32(Bytes, Address, Size, Insn);

    if (Result == MCDisassembler::Fail) return MCDisassembler::Fail;

    Result = decodeInstruction(getDecoderTable(Size), Instr, Insn,
                               Address, this, STI);

    if (Result != MCDisassembler::Fail) {
      return Result;
    }

    return MCDisassembler::Fail;
  }
}

typedef DecodeStatus (*DecodeFunc)(MCInst &MI, unsigned insn, uint64_t Address,
                                   const void *Decoder);

