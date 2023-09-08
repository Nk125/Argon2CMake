## Argon2CMake

Just a wrapper of Argon2 in CMake, i was surprised that nobody did it until now i'm coding it, or just i'm too bad searching

### What it does

First of all, we have the next table of things to do:

1. Download the repo of [Argon2](https://github.com/P-H-C/phc-winner-argon2) 

2. Index include directory and all source files

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
target_link_libraries(myexe Argon2)
```

You'll have in your project Argon2!

## Some configs

Maybe you'll want to use the reference version (in plain C) of Argon2 or the optimized version (with assembly optimizations, and default version compiled), so there are some options you want to check

* ARGON2_REF_CODE

To be used in case you want plain C Argon2 Code

* ARGON2_ASM_CODE (Default)

The default option, and preferred if both are set to true, use the optimized assembly Argon2 code
