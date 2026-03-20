add_library(SDL3_Interface INTERFACE)

if(WIN32)
    target_include_directories(SDL3_Interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/include")
    target_link_libraries(SDL3_Interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/lib/x64/SDL3.lib")
else()
    find_package(SDL3 REQUIRED)
    target_link_libraries(SDL3_Interface INTERFACE SDL3::SDL3)
endif()