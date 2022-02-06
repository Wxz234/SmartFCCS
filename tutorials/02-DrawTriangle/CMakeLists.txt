add_executable(02-DrawTriangle WIN32 main.cpp)
target_link_libraries(02-DrawTriangle PRIVATE SmartFCCS d3dcompiler)
set_target_properties(02-DrawTriangle PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET 02-DrawTriangle POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SmartFCCS> $<TARGET_FILE_DIR:02-DrawTriangle>)