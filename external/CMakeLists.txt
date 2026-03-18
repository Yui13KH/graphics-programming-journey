# exports sdl3 to the rest of the project

add_library(SDL3_Interface INTERFACE)

target_include_directories(SDL3_Interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/include")

target_link_libraries(SDL3_Interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/lib/x64/SDL3.lib")

set(SDL3_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/bin/x64" CACHE INTERNAL "")