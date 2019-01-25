cmake_minimum_required(VERSION 3.8)

project(PowerPMAC_CoordinateSystems VERSION 1.0 DESCRIPTION "tango ppmac corrdinate system library" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(PowerPMAC_CoordinateSystems STATIC PowerPMAC_CoordinateSystems.cpp
        PowerPMAC_CoordinateSystemsClass.cpp
        PowerPMAC_CoordinateSystemsStateMachine.cpp)

# all other includeded cmake files will have this
include_directories(PUBLIC SYSTEM /usr/include/tango)
target_include_directories(PowerPMAC_CoordinateSystems PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../ppmac_core ../wise_enum-master)

link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)
target_link_libraries(PowerPMAC_CoordinateSystems PRIVATE tango omniDynamic4 COS4 omniORB4 omnithread log4tango zmq dl pthread stdc++ ppmac_core)