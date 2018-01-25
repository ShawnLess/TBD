//===-- TBD.td - Describe the TBD Target Machine -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// TBD processors supported.
//===----------------------------------------------------------------------===//
// 'TBDItineraries' is a def in TBDSchedule.td
class TBDProcessor<string name, list<SubtargetFeature> features = []> :
	  		ProcessorModel<name, NoSchedModel, features>;

def : TBDProcessor<"TBD">; // -mcpu=xxxxx

//===----------------------------------------------------------------------===//
// Register File Description
//===----------------------------------------------------------------------===//
include "TBDRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Instruction Descriptions
//===----------------------------------------------------------------------===//
include "TBDInstrInfo.td"

def TBDInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Target Declaration
//===----------------------------------------------------------------------===//
//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//
def TBD : Target {
 let InstructionSet = TBDInstrInfo;
}
