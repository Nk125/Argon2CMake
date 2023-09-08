## Argon2CMake

Just a wrapper of Argon2 in CMake, i was surprised that nobody did it until now i'm coding it, or just i'm too bad searching

### What it does

The CMakeLists file:

1. Downloads the repo of [Argon2](https://github.com/P-H-C/phc-winner-argon2) 

2. Indexes include directory and all source files

3. Makes a bundle of all into a **static library**

### How to use

Just add something like:

```cmake
include(FetchContent)

FetchContent_Declare(
    Argon2CMake
    GIT_REPOSITORY https://github.com/Nk125/Argon2CMake
    GIT_TAG main
)

FetchContent_MakeAvailable(Argon2CMake)
```

And then

```cmake
target_link_libraries(myexe PRIVATE Argon2)
```

You'll have in your project Argon2!

## Some configs

Maybe you'll want to use the reference version (in plain C) of Argon2 or the optimized version (with assembly optimizations, and default version compiled), so there are some options you want to check

* ARGON2_USE_ASM_CODE (Default: true)

Use the optimized assembly code for some CPUs, if set to false the library will compile with reference C plain code

This is useful with ARM CPUs, that aren't covered by the assembly optimizations in Argon2

* ARGON2_USE_THREADS (Default: true)

Enable the threading Argon2 built-in capability, you can disable or enable in order of your needs
