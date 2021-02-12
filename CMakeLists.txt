cmake_minimum_required(VERSION 3.2)
project(symicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

set(SOURCE_FILES main.cpp)

add_library(symiwrap SHARED QuiltIcon.cpp
        QuiltIcon.h ColourIcon.cpp ColourIcon.h SymIconApp.cpp SymIconApp.h)
#add_library(symidart SHARED DartSymi.cpp symi_interface.cpp)
add_executable(symicon ${SOURCE_FILES} )
add_library(emutil SHARED IMPORTED)
set_property(TARGET emutil PROPERTY IMPORTED_LOCATION "/home/peter/CLionProjects/emu/cmake-build-debug/utility/libemutil.so")
#set_property(TARGET symidart PROPERTY "DART_SHARED_LIB")
set_property(TARGET symiwrap PROPERTY "DART_SHARED_LIB")
#include_directories(/usr/include/cairo /home/peter/tools/flutter/bin/cache/dart-sdk/include)
include_directories(../emu/utility)

link_directories(/usr/lib/x86_64-linux-gnu ../emu/utility)
#target_link_libraries(symiwrap libcairo.so.2 emutil symidart)
#target_link_libraries(symicon symiwrap)
#target_link_libraries(symidart symiwrap)
