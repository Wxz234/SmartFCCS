add_executable(03-Camera WIN32 main.cpp)
target_link_libraries(03-Camera PRIVATE SmartFCCS d3dcompiler)
set_target_properties(03-Camera PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET 03-Camera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SmartFCCS> $<TARGET_FILE_DIR:03-Camera>)