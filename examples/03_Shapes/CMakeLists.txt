add_executable(03_Shapes main.cpp)

target_link_libraries(03_Shapes PRIVATE Core_Interface SDL3_Interface)

if(WIN32)
    add_custom_command(TARGET 03_Shapes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:03_Shapes>
        COMMENT "Copying SDL3.dll to binary directory"
    )
endif()