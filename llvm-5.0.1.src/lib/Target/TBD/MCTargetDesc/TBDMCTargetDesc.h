//===-- TBDMCTargetDesc.h - TBD Target Descriptions -------------*- C++ -*-===//
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

#ifndef LLVM_TBD_MCTARGET_DESC_H
#define LLVM_TBD_MCTARGET_DESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectWriter;
class MCRegisterInfo;
class MCTargetOptions;
class StringRef;
class Target;
class Triple;
class raw_pwrite_stream;

Target &getTheTBDTarget();
} // end namespace llvm
#endif // LLVM_TBD_MCTARGET_DESC_H
