cmake_minimum_required(VERSION 3.8)

project(PowerPMAC VERSION 1.0 DESCRIPTION "Power PMAC Tango Server" LANGUAGES CXX)

# genereal compilation options we want to use
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra") #-fasynchronous-unwind-tables -fexceptions -fpie -Wl,-pie -fpic -shared -grecord-gcc-switches
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Winvalid-pch -Wmissing-prototypes")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -flto -Wodr -Wpointer-arith -Wshadow -Wcast-qual -Wstrict-aliasing=1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Werror=return-type -Wsign-compare -Wduplicated-cond -Wlogical-op -Wnull-dereference") #-Wduplicated-branches (7+)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wuseless-cast -Wjump-misses-init")

# -pg for progiling with gprof
# gcc only options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wlogical-op -Wuseless-cast -Wno-shadow -Wno-pragmas -Wno-unused-variable -Wno-unused-parameter") #-Wself-assign"
endif()

# add debug/release specific flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_FORTIFY_SOURCE=2") #-D_GLIBCXX_DEBUG
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")

#set(CMAKE_VERBOSE_MAKEFILE ON)

# this is the program dependency we will build
add_executable(PowerPMAC main.cpp MultiClassesFactory.cpp tangoutil.cpp)

# all other includeded cmake files will have this
include_directories(SYSTEM /usr/include/tango)
link_directories(/usr/lib/x86_64-linux-gnu/ /usr/lib/)

add_subdirectory(powerpmac_coordinatesystems)
add_subdirectory(powerpmac_global)
add_subdirectory(powerpmac_io)
add_subdirectory(powerpmac_motor)
add_subdirectory(powerpmac_programs)
add_subdirectory(powerpmac_plc)
add_subdirectory(ppmac_core)
# external but intree libraries
#add_subdirectory(powerPMAC_ssh-master)
add_subdirectory(fmt-5.3.0)
add_subdirectory(spdlog-1.3.0)
#add_subdirectory(libssh2-master)

# this is only for this main project
target_include_directories(PowerPMAC PUBLIC powerpmac_coordinatesystems)
target_include_directories(PowerPMAC PUBLIC powerpmac_global)
target_include_directories(PowerPMAC PUBLIC powerpmac_io)
target_include_directories(PowerPMAC PUBLIC powerpmac_motor)
target_include_directories(PowerPMAC PUBLIC powerpmac_programs)
target_include_directories(PowerPMAC PUBLIC powerpmac_plc)
# only needed if we want the multi server stuff to access ppmac core. can be usefull for easy debugging untill we make an own testptroject for that
target_include_directories(PowerPMAC PUBLIC ppmac_core)

#-ltango -lomniDynamic4 -lCOS4 -lomniORB4 -lomnithread -llog4tango -lzmq -ldl -lpthread -lstdc++
target_link_libraries(PowerPMAC tango omniDynamic4 COS4 omniORB4 omnithread log4tango zmq dl pthread stdc++
        ppmac_core # only for current debugging of the ppmac library
        #fmt
        #spdlog
        PowerPMAC_CoordinateSystems
        PowerPMAC_Global
        PowerPMAC_IO
        PowerPMAC_Motor
        PowerPMAC_Programs
        PowerPMAC_PLC)