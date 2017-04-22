cmake_minimum_required(VERSION 3.2)
project(symicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    QuiltIcon.cpp
    QuiltIcon.h PaintIcon.cpp PaintIcon.h)

add_executable(symicon ${SOURCE_FILES} )
add_library(emutil SHARED IMPORTED)
set_property(TARGET emutil PROPERTY IMPORTED_LOCATION "/home/peter/ClionProjects/function_utilities/cmake-build-debug/utility/libemutil.so")
include_directories(/usr/include/cairo)
include_directories(../function_utilities/utility)

link_directories(/usr/lib/x86_64-linux-gnu ../function_utilities/utility)
target_link_libraries(symicon libcairo.so.2 emutil)
