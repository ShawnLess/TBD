set(LLVM_TARGET_DEFINITIONS TBD.td)

tablegen(LLVM TBDGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(TBDCommonTableGen)
add_llvm_target(TBDCodeGen
  TBDTargetMachine.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
