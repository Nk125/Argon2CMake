cmake_minimum_required(VERSION 3.15)

project(Argon2)

option(ARGON2_USE_ASM_CODE "Compile with optimized assembly code" ON)

option(ARGON2_USE_THREADS "Compile with threading capability" ON)

include("FetchContent")

FetchContent_Declare(
    Argon2DW
    GIT_REPOSITORY https://github.com/P-H-C/phc-winner-argon2
    GIT_TAG master
)

FetchContent_GetProperties(Argon2DW)

if (NOT ${argon2dw_POPULATED})
    message(STATUS "Argon2: Populating")

    FetchContent_Populate(Argon2DW)
endif()

set(Argon2SrcPath "${argon2dw_SOURCE_DIR}/src")

add_library(Argon2 STATIC    
    "${Argon2SrcPath}/argon2.c"
    "${Argon2SrcPath}/core.c"
    "${Argon2SrcPath}/encoding.c"
    "${Argon2SrcPath}/blake2/blake2b.c"
)

target_include_directories(Argon2 PUBLIC "${argon2dw_SOURCE_DIR}/include" PRIVATE "${Argon2SrcPath}")

if (WIN32)
    target_compile_definitions(Argon2 PRIVATE _CRT_SECURE_WARNINGS)
endif()

if (ARGON2_USE_THREADS)
    message(STATUS "Argon2: Enabled threading")

    find_package(Threads REQUIRED)

    target_sources(Argon2 PRIVATE "${Argon2SrcPath}/thread.c")

    target_link_libraries(Argon2 PRIVATE Threads::Threads)
else()
    message(STATUS "Argon2: Disabled threading")

    target_compile_definitions(Argon2 PRIVATE ARGON2_NO_THREADS)
endif()

if (ARGON2_USE_ASM_CODE)
    target_sources(Argon2 PRIVATE "${Argon2SrcPath}/opt.c")

    message(STATUS "Argon2: Setting up with optimized assembly code")
else()
    target_sources(Argon2 PRIVATE "${Argon2SrcPath}/ref.c")

    message(STATUS "Argon2: Building with reference C plain code")
endif()

message(STATUS "Argon2: Configured succesfully")
