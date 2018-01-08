add_llvm_library(LLVMTBDDesc
  TBDMCTargetDesc.cpp
  TBDMCAsmInfo.cpp
)

add_dependencies(LLVMTBDDesc TBDCommonTableGen)
