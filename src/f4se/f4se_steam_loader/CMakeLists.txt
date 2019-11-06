add_compile_definitions(
  _USRDLL
  F4SE_STEAM_LOADER_EXPORTS
)

add_library(f4se_steam_loader SHARED
  ../f4se_common/f4se_version.rc
  main.cpp
)

target_link_libraries(f4se_steam_loader common f4se_common f4se_loader_common version)
