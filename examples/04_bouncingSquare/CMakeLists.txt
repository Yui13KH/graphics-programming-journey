add_executable(04_bouncingSquare main.cpp)

target_link_libraries(04_bouncingSquare PRIVATE Core_Interface SDL3_Interface)

if(WIN32)
    add_custom_command(TARGET 04_bouncingSquare POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:04_bouncingSquare>
        COMMENT "Copying SDL3.dll to binary directory"
    )
endif()