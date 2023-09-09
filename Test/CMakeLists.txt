cmake_minimum_required(VERSION 3.15)

# This is independent to the top level project

project(TestArgonHash)

include(FetchContent)

FetchContent_Declare(
    Argon2CMake
    GIT_REPOSITORY https://github.com/Nk125/Argon2CMake
    GIT_TAG main
)

FetchContent_MakeAvailable(Argon2CMake)

add_executable(TestArgonHash "main.cpp")

target_link_libraries(TestArgonHash PRIVATE Argon2)