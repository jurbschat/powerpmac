cmake_minimum_required(VERSION 3.8)

project(ppmac_core VERSION 1.0 DESCRIPTION "power pmac core classes" LANGUAGES CXX)
project(ppmac_core_test VERSION 1.0 DESCRIPTION "power pmac core classes" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fasynchronous-unwind-tables -fexceptions -grecord-gcc-switches")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Winvalid-pch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Wodr -Wpointer-arith -Wshadow -Wcast-qual -Wstrict-aliasing=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Werror=return-type -Wsign-compare -Wnull-dereference") #-Wduplicated-branches (gcc 7+)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wno-shadow ") #-Wself-assign"

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_FORTIFY_SOURCE=2")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE SPDLOG_FMT_EXTERNAL)

# maybe add this stuff, check what we actually want
## linker stuff -fpie -Wl,-pie -fpic -shared

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wlogical-op -Wuseless-cast -Wno-shadow -Wno-pragmas -Wno-unused-variable -Wno-unused-parameter -Wno-useless-cast") #-Wself-assign"
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(ppmac_core STATIC coreinterface.cpp
        core.cpp
        remoteshell.cpp
        receivebuffer.cpp
        utility.cpp
        test-main.cpp
        exception.cpp
        udpsink.cpp
        uuid.cpp
        commandbuilder.cpp
        resultparser.cpp
        config.cpp
        throw.cpp
        stateupdater.cpp
        locking.cpp
        threading.cpp
        pmac/defines.cpp
        pmac/datastructures.cpp)

target_include_directories(ppmac_core SYSTEM PRIVATE ../fmt-5.3.0/include ../spdlog-1.3.0/include ../wise_enum-master ../catch2-master/single_include ../type_safe-master/include ../type_safe-master/external/debug_assert)
target_link_libraries(ppmac_core PRIVATE stdc++ fmt spdlog ssh2 boost_system boost_regex pthread dl)

# test stuff

add_executable(ppmac_core_test test-main.cpp test-tests.cpp)
target_include_directories(ppmac_core_test SYSTEM PRIVATE ../fmt-5.3.0/include ../spdlog-1.3.0/include ../wise_enum-master ../catch2-master/single_include ../type_safe-master/include ../type_safe-master/external/debug_assert)
target_link_libraries(ppmac_core_test PRIVATE stdc++ fmt spdlog boost_system boost_regex ssh2 ppmac_core)
#set_target_properties(ppmac_core_test PROPERTIES COMPILE_FLAGS -DMUH)

add_executable(ppmac_core_profile main.cpp)
target_include_directories(ppmac_core_profile SYSTEM PRIVATE ../fmt-5.3.0/include ../spdlog-1.3.0/include ../wise_enum-master ../catch2-master/single_include ../type_safe-master/include ../type_safe-master/external/debug_assert)
target_link_libraries(ppmac_core_profile PRIVATE stdc++ fmt spdlog ssh2 boost_system boost_regex ppmac_core pthread)