//===-- TBDRegisterInfo.td - TBD Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the TBD register file
//===----------------------------------------------------------------------===//

class TBDReg<bits<5> num, string n > : Register<n> {
  let Namespace = "TBDReg";
}

//Define 32 register x0-x31
foreach i = 0-31 in {
  def x#i   : TBDReg<i, "x"#i >, DwarfRegNum< [i] >;
}

//define the register class
// 
// class RegisterClass<string namespace, list<ValueType> regTypes, int alignment,
//                     dag regList, RegAltNameIndex idx = NoRegAltName>
//   : DAGOperand {
def GPR : RegisterClass<"TBDReg", [i32], 32, (add (sequence "x%u", 0, 31) )>;

