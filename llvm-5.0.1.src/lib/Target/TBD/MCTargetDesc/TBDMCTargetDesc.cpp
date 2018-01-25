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
#include "InstPrinter/TBDInstPrinter.h"

//This will declare the InitTBDMCInstrInfo() function
#define GET_INSTRINFO_MC_DESC
#include "TBDGenInstrInfo.inc"

//This will declare the InitTBDMCRegisterInfo() function
#define GET_REGINFO_MC_DESC
#include "TBDGenRegisterInfo.inc"

using namespace llvm;

static MCRegisterInfo * createTBDMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTBDMCRegisterInfo(X, 0);    // 0 is used to disguise return address register.
  return X;
}

static MCInstrInfo *createTBDMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTBDMCInstrInfo(X);
  return X;
}


static MCInstPrinter *createTBDMCInstPrinter(const 	Triple &TT,
                                             unsigned 	SyntaxVariant,
                                             const 	MCAsmInfo &MAI,
                                             const 	MCInstrInfo &MII,
                                             const 	MCRegisterInfo &MRI) {
  return new TBDInstPrinter(MAI, MII, MRI);
}


extern "C" void LLVMInitializeTBDTargetMC() {
  // Register the MC asm info, using the default settings.
  RegisterMCAsmInfo<TBDMCAsmInfo> X( getTheTBDTarget() );

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo( getTheTBDTarget(), createTBDMCRegisterInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo( getTheTBDTarget(), createTBDMCInstrInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter( getTheTBDTarget(), createTBDMCInstPrinter);
}

