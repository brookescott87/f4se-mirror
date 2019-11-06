cmake_minimum_required(VERSION 3.12.2)
cmake_policy(SET CMP0076 NEW)

project(f4se VERSION 1.10.106)
string(JOIN "_" F4SE_VERSION_TAG
    ${PROJECT_VERSION_MAJOR}
    ${PROJECT_VERSION_MINOR}
    ${PROJECT_VERSION_PATCH}
    ${PROJECT_VERSION_TWEAK}
)
math(EXPR F4SE_VERSION_HEX
    "0${PROJECT_VERSION_MAJOR} * 0x1000000 + \
    0${PROJECT_VERSION_MINOR} * 0x10000 + \
    0${PROJECT_VERSION_PATCH} * 0x10 + \
    0${PROJECT_VERSION_TWEAK}"
    OUTPUT_FORMAT HEXADECIMAL)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    CACHE INTERNAL "" FORCE)

# Preprocessor definitions
add_compile_definitions(
  $<$<CONFIG:Debug>:_DEBUG>
)

if (MSVC)
  add_compile_options(/FI"common/IPrefix.h")
endif ()

include_directories(.)

add_subdirectory(common)
add_subdirectory(f4se)
