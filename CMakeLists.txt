cmake_minimum_required(VERSION 3.15)

project(Argon2CMake)

option(ARGON2_ASM_CODE "Compile with optimized assembly code" ON)

option(ARGON2_REF_CODE "Compile with plain C code" OFF)

include("FetchContent")

FetchContent_Declare(
    Argon2
    GIT_REPOSITORY https://github.com/P-H-C/phc-winner-argon2
    GIT_TAG master
)

FetchContent_GetProperties(Argon2)

if (NOT ${argon2_POPULATED})
    FetchContent_Populate(Argon2)
endif()

set(Argon2SrcPath "${argon2_SOURCE_DIR}/src")

add_library(Argon2CMake STATIC
    "${Argon2SrcPath}/argon2.c"
    "${Argon2SrcPath}/core.c"
    "${Argon2SrcPath}/encoding.c"
    "${Argon2SrcPath}/thread.c"
    "${Argon2SrcPath}/blake2/blake2b.c"
)

target_include_directories(Argon2CMake PUBLIC $<BUILD_INTERFACE:${argon2_SOURCE_DIR}/include>)

if (WIN32)
    target_compile_definitions(Argon2CMake PRIVATE _CRT_SECURE_WARNINGS)
endif()

if (ARGON2_ASM_CODE)
    target_sources(Argon2CMake PUBLIC "${Argon2SrcPath}/opt.c")
else()
    target_sources(Argon2CMake PUBLIC "${Argon2SrcPath}/ref.c")
endif()

message(STATUS "Argon2: Built succesfully")