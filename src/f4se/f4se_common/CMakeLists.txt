add_compile_definitions(_LIB)

add_library(f4se_common STATIC
  BranchTrampoline.cpp
  BranchTrampoline.h
  f4se_version.h
  f4se_version.rc
  Relocation.cpp
  Relocation.h
  SafeWrite.cpp
  SafeWrite.h
  Utilities.cpp
  Utilities.h
)