cmake_minimum_required(VERSION 3.8)

project(PowerPMAC_PLC VERSION 1.0 DESCRIPTION "tango ppmac plc library" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-pragmas -Wno-useless-cast")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(PowerPMAC_PLC STATIC PowerPMAC_PLC.cpp
        PowerPMAC_PLCClass.cpp
        PowerPMAC_PLCStateMachine.cpp)

# all other includeded cmake files will have this
include_directories(PUBLIC SYSTEM /usr/include/tango)
target_include_directories(PowerPMAC_PLC PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../ppmac_core ../fmt-5.3.0/include ../type_safe-master/include)

link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)

#-ltango -lomniDynamic4 -lCOS4 -lomniORB4 -lomnithread -llog4tango -lzmq -ldl -lpthread -lstdc++
target_link_libraries(PowerPMAC_PLC PRIVATE tango omniDynamic4 COS4 omniORB4 omnithread log4tango zmq dl pthread stdc++ ppmac_core)