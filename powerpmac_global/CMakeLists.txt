cmake_minimum_required(VERSION 3.8)

project(PowerPMAC_Global VERSION 1.0 DESCRIPTION "tango ppmac corrdinate system library" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

if(CMAKE_CXX_COMPILER MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-pragmas")
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(PowerPMAC_Global STATIC PowerPMAC_Global.cpp
        PowerPMAC_GlobalClass.cpp
        PowerPMAC_GlobalStateMachine.cpp)

# all other includeded cmake files will have this
include_directories(PUBLIC SYSTEM /usr/include/tango)
target_include_directories(PowerPMAC_Global PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../ppmac_core ../wise_enum-master)

link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)
target_link_libraries(PowerPMAC_Global PRIVATE tango omniDynamic4 COS4 omniORB4 omnithread log4tango zmq dl pthread stdc++ ppmac_core)