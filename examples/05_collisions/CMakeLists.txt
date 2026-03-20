add_executable(05_collisions main.cpp)

target_link_libraries(05_collisions PRIVATE Core_Interface SDL3_Interface)

if(WIN32)
    add_custom_command(TARGET 05_collisions POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:05_collisions>
        COMMENT "Copying SDL3.dll to binary directory"
    )
endif()