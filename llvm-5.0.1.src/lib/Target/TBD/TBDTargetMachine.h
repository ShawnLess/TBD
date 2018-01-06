//===-- TBDTargetMachine.h - Define TargetMachine for TBD -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the TBD specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TBD_TARGET_MACHINE_H
#define LLVM_TBD_TARGET_MACHINE_H

#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

/// A generic TBD implementation.
class TBDTargetMachine : public LLVMTargetMachine {
public:
  TBDTargetMachine( const Target 	&T 
	          , const Triple 	&TT 
		  , StringRef 		CPU
                  , StringRef 		FS
                  , const TargetOptions &Options
                  , Optional<Reloc::Model> 	RM
		  , CodeModel::Model 		CM
	          , CodeGenOpt::Level 		OL);
};

} // end namespace llvm

#endif // LLVM_TBD_TARGET_MACHINE_H
