cmake_minimum_required(VERSION 3.8)

project(PowerPMAC_IO VERSION 1.0 DESCRIPTION "tango ppmac corrdinate system library" LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

if(CMAKE_CXX_COMPILER MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-pragmas")
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(PowerPMAC_IO STATIC PowerPMAC_IO.cpp
        PowerPMAC_IOClass.cpp
        PowerPMAC_IOStateMachine.cpp)

# all other includeded cmake files will have this
include_directories(PUBLIC SYSTEM /usr/include/tango)
target_include_directories(PowerPMAC_IO PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../ppmac_core ../fmt-5.3.0/include)

link_directories(PUBLIC /usr/lib/x86_64-linux-gnu/ /usr/lib/)

#-ltango -lomniDynamic4 -lCOS4 -lomniORB4 -lomnithread -llog4tango -lzmq -ldl -lpthread -lstdc++
target_link_libraries(PowerPMAC_IO PRIVATE tango omniDynamic4 COS4 omniORB4 omnithread log4tango zmq dl pthread stdc++ ppmac_core)