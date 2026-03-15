cmake_minimum_required(VERSION 3.10)
project(Boilerplate)

set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/SDL3/cmake")

find_package(SDL3 REQUIRED CONFIG)

add_executable(Boilerplate main.cpp)

target_link_libraries(Boilerplate PRIVATE SDL3::SDL3)

if(MSVC)
    set_target_properties(Boilerplate PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()