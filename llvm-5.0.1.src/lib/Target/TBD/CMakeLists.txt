set(LLVM_TARGET_DEFINITIONS TBD.td)

tablegen(LLVM TBDGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TBDGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TBDGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TBDGenDisassemblerTables.inc -gen-disassembler)

add_public_tablegen_target(TBDCommonTableGen)
add_llvm_target(TBDCodeGen
  TBDTargetMachine.cpp
)

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(Disassembler)
