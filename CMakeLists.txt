cmake_minimum_required(VERSION 3.2)
project(symicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_library(symiwrap SHARED QuiltIcon.cpp
        QuiltIcon.h PaintIcon.cpp PaintIcon.h SymIconApp.cpp SymIconApp.h JniSymi.cpp JniSymi.h)
add_executable(symicon ${SOURCE_FILES} )
add_library(emutil SHARED IMPORTED)
set_property(TARGET emutil PROPERTY IMPORTED_LOCATION "/home/peter/CLionProjects/emu/cmake-build-debug/utility/libemutil.so")
include_directories(/usr/include/cairo)
include_directories(../emu/utility)

link_directories(/usr/lib/x86_64-linux-gnu ../emu/utility)
target_link_libraries(symiwrap libcairo.so.2 emutil)
target_link_libraries(symicon symiwrap)
