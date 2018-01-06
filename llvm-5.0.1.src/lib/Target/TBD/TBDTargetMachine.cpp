//===-- TBDTargetMachine.cpp - Define TargetMachine for TBD ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the TBD specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#include "TBDTargetMachine.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

#include "MCTargetDesc/TBDMCTargetDesc.h"
namespace llvm {
//-----------------------------------------------------------------------------
// 1. The construction function
static const char *dl = "";
TBDTargetMachine::TBDTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Optional<Reloc::Model> RM, CodeModel::Model CM,
                                   CodeGenOpt::Level OL)
    //[DataLayoutString]: is '' so the target will used the default data layout.
    // 		          Refer to "Data Layout" https://llvm.org/docs/LangRef.html#langref-datalayout 
    : LLVMTargetMachine( T, dl, TT, CPU, FS, Options, *RM, CM, OL) {

  initAsmInfo();
}

//-----------------------------------------------------------------------------
// 2. The registration function
//Target& llvm::getTheTBDTarget();
extern "C" void LLVMInitializeTBDTarget() {
  // Register the target.
  RegisterTargetMachine< TBDTargetMachine > X( getTheTBDTarget() );
}

} // end of namespace llvm

