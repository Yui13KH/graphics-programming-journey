#core libary for just headers

add_library(Core_Interface INTERFACE)

target_include_directories(Core_Interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")