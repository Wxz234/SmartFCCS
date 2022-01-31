add_executable(01-InitializeDevice WIN32 main.cpp)
target_link_libraries(01-InitializeDevice PRIVATE SmartFCCS)

add_custom_command(TARGET 01-InitializeDevice POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SmartFCCS> $<TARGET_FILE_DIR:01-InitializeDevice>)