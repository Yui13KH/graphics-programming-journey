# 1. Create the executable target
add_executable(02_RedWindow main.cpp)

# 2. Link the core and SDL3 interfaces
target_link_libraries(02_RedWindow PRIVATE Core_Interface SDL3_Interface)

# 3. Handle the DLL copy AFTER the target is created in THIS file
add_custom_command(TARGET 02_RedWindow POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../external/SDL3/lib/x64/SDL3.dll"
    $<TARGET_FILE_DIR:02_RedWindow>
    COMMENT "Copying SDL3.dll to binary directory"
)