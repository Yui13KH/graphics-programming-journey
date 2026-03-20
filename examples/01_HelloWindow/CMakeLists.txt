add_executable(01_HelloWindow main.cpp)

target_link_libraries(01_HelloWindow PRIVATE Core_Interface SDL3_Interface)

if(WIN32)
    add_custom_command(TARGET 01_HelloWindow POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:01_HelloWindow>
        COMMENT "Copying SDL3.dll to binary directory"
    )
endif()