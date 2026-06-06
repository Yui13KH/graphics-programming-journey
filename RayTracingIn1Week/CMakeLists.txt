cmake_minimum_required(VERSION 3.20)
project(RayTracer LANGUAGES CXX)

# Force C++20 (highly recommended for modern, clean C++ features)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your main executable and its source files
add_executable(RayTracer ppm.cpp)

# (Optional) Setup compiler warnings to catch bugs early
if(MSVC)
    target_compile_options(RayTracer PRIVATE /W4)
else()
    target_compile_options(RayTracer PRIVATE -Wall -Wextra -Wpedantic)
endif()