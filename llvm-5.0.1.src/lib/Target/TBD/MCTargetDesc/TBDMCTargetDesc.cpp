//===-- TBDMCTargetDesc.cpp - TBD Target Descriptions ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TBD specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
/*
#define GET_INSTRINFO_MC_DESC
#include "TBDGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TBDGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TBDGenRegisterInfo.inc"
*/
using namespace llvm;

extern "C" void LLVMInitializeTBDTargetMC() {
}

