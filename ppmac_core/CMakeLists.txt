cmake_minimum_required(VERSION 3.8)

project(ppmac_core VERSION 1.0 DESCRIPTION "power pmac core classes" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fasynchronous-unwind-tables -fexceptions -grecord-gcc-switches")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Winvalid-pch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Wodr -Wpointer-arith -Wshadow -Wcast-qual -Wstrict-aliasing=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Werror=return-type -Wsign-compare -Wnull-dereference") #-Wduplicated-branches (gcc 7+)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast ") #-Wself-assign"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments") # supported by gcc/clang/msvc

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG")

add_definitions(-DSPDLOG_FMT_EXTERNAL)
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

# gcc only options
if(CMAKE_CXX_COMPILER MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wlogical-op -Wuseless-cast") #-Wself-assign"
endif()

# maybe add this stuff, check what we actually want
## linker stuff -fpie -Wl,-pie -fpic -shared

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(ppmac_core STATIC coreinterface.cpp
        core.cpp
        remoteshell.cpp
        receivebuffer.cpp
        utility.cpp
        test.cpp
        pmac/defines.cpp)

target_include_directories(ppmac_core PRIVATE SYSTEM ../fmt-5.3.0/include ../spdlog-1.3.0/include ../wise_enum-master)

# all other includeded cmake files will have this
#include_directories(PUBLIC /usr/include/tango)
#link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)

target_link_libraries(ppmac_core PRIVATE stdc++ fmt spdlog ssh2 ) #ssh2 rt pthread libPowerPmacControl boost_system crypto ssl