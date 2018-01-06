#!/bin/bash
root=`pwd`

# Check argument
llvm_en=1
debug_mode=1
install_path=
while (( $# != 0 ))
do
  case $1 in
  "--disable-llvm" )
     llvm_en=0
     shift
  ;;
  "-h" )
    echo "Usage of $0:"
    echo -e "\t-h\t\t\t\tShow this list"
    echo -e "\t--disable-llvm\t\t\tDo not install llvm toolchain"
    echo -e "\t--enable-xxx\t\tInstall xxx package"
    echo -e "\t--disable-all\t\tDo not install anything (used with following --enable-xxx)"
    echo -e "\t--enable-debug\t\tBuild in debug and incremental mode, and do not remove the building dirs"
    exit 0
  ;;
  * )
    if [ -n "$install_path" ]
    then
      echo "Unknown argument $1, try $0 -h to see the usage"
      exit 1
    fi
    echo "Install to $1."
    if [[ $1 != /* ]]
    then
      echo "Install path must be absolute."
      exit 1
    fi
    install_path=$1
    source_path=$(dirname `readlink -e $0`)
    shift
  ;;
  esac
done

# Define multi-core option
MCFLAG='-j 64'

# Switch debug mode
if [ "$debug_mode" -eq 1 ]; then
  gem5_opt_mode='.debug'
  llvm_cfg='Debug'
else
  gem5_opt_mode='.opt'
  llvm_cfg='Release'
fi

# Initialize error status
llvm_err=0

# Install llvm
if [ "$llvm_en" -eq 1 ]; then
  cd $root
  if [ -e "build_llvm" ] && [ "$debug_mode" -eq 0 ]; then 
	rm -rf build_llvm
  fi
  if [ ! -e "build_llvm" ]; then 
	mkdir build_llvm
  fi
  cd build_llvm
  cmake $source_path/llvm-5.0.1.src -DLLVM_TARGETS_TO_BUILD="X86" -DCMAKE_INSTALL_PREFIX=$install_path -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD="TBD"
  make $MCFLAG || llvm_err=1
  if [ "$debug_mode" -eq 0 ]; then 
    make install
  fi
fi

# Clean up all temporary files
cd $root
if [ "$debug_mode" -eq 0 ]; then
  if [ "$llvm_err" -eq 0 ]; then 
	rm -rf build_llvm
  else 
	echo "Failed to install LLVM"
  fi
fi
