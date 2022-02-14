add_executable(04-MultithreadedRendering WIN32 main.cpp)
target_link_libraries(04-MultithreadedRendering PRIVATE SmartFCCS)

add_custom_command(TARGET 04-MultithreadedRendering POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SmartFCCS> $<TARGET_FILE_DIR:04-MultithreadedRendering>)