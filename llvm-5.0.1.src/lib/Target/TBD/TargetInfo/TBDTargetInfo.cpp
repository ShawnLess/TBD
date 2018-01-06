//===-- TBDTargetInfo.cpp - TBD Target Implementation ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
namespace llvm {
Target & getTheTBDTarget() {
  static Target TheTBDTarget;
  return TheTBDTarget;
}
}

extern "C" void LLVMInitializeTBDTargetInfo() {
  llvm::RegisterTarget<llvm::Triple::tbd> X(llvm::getTheTBDTarget(), "tbd",
                                            "TBD Generator");
}

