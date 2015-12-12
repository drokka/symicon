cmake_minimum_required(VERSION 3.2)
project(symicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    QuiltIcon.cpp
    QuiltIcon.h )

add_executable(symicon ${SOURCE_FILES} )

include_directories(/usr/include/cairo)
include_directories(../function_utilities/utility)

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(symicon libcairo.so.2)
