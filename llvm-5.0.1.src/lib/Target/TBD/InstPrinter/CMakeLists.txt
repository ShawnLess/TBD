add_llvm_library(LLVMTBDAsmPrinter
  TBDInstPrinter.cpp
  )
add_dependencies(LLVMTBDAsmPrinter TBDCommonTableGen)
