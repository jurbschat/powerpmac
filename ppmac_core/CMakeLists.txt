cmake_minimum_required(VERSION 3.8)

project(ppmac_core VERSION 1.0 DESCRIPTION "power pmac core classes" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fasynchronous-unwind-tables -fexceptions -grecord-gcc-switches")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Winvalid-pch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Wodr -Wpointer-arith -Wshadow -Wcast-qual -Wstrict-aliasing=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Werror=return-type -Wsign-compare -Wduplicated-cond -Wlogical-op -Wnull-dereference") #-Wduplicated-branches (7+)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wuseless-cast")
## linker stuff -fpie -Wl,-pie -fpic -shared

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(ppmac_core STATIC ppmaccoreinterface.cpp)

# all other includeded cmake files will have this
#include_directories(PUBLIC /usr/include/tango)
#link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)

target_link_libraries(ppmac_core PRIVATE stdc++)