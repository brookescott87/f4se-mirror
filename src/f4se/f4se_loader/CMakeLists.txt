add_compile_definitions(_CONSOLE)

add_executable(f4se_loader
  ../f4se_common/f4se_version.rc
  main.cpp
  Options.cpp
  Options.h
)

target_link_libraries(f4se_loader common f4se_common f4se_loader_common version)
