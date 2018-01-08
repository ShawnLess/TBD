//===-- TBDMCAsmInfo.h - TBD asm properties ---------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the TBDMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TBD_ASM_INFO_H
#define LLVM_TBD_ASM_INFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {

class Triple;

/// Specifies the format of TBD assembly files.
class TBDMCAsmInfo : public MCAsmInfo {
public:
  explicit TBDMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_TBD_ASM_INFO_H
