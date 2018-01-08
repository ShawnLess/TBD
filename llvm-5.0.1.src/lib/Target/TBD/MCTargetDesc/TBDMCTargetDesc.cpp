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

#include "TBDMCAsmInfo.h"
#include "TBDMCTargetDesc.h"

using namespace llvm;

static MCRegisterInfo *
createTBDMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}



extern "C" void LLVMInitializeTBDTargetMC() {
  // Register the MC asm info, using the default settings.
  RegisterMCAsmInfo<TBDMCAsmInfo> X( getTheTBDTarget() );

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo( getTheTBDTarget(), createTBDMCRegisterInfo);
}

