cmake_minimum_required(VERSION 3.20)
project(GraphicsJourney LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")

add_subdirectory(external)
add_subdirectory(core)
add_subdirectory(examples)