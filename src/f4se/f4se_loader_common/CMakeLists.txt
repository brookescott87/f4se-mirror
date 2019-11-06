add_compile_definitions(_LIB)

add_library(f4se_loader_common STATIC
  IdentifyEXE.cpp
  IdentifyEXE.h
  Inject.cpp
  Inject.h
  LoaderError.cpp
  LoaderError.h
  Steam.cpp
  Steam.h
)