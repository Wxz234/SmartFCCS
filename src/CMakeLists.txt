set(FCCS_INCLUDE_DIRECTION 
    ${PROJECT_SOURCE_DIR}/include
)
set(FCCS_INCLUDE_FILE 
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/SmartFCCS.h
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/Core.h
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/Window.h
)

set(FCCS_SOURCE_FILE
    SmartFCCS.cpp
)

add_library(SmartFCCS SHARED 
    ${FCCS_SOURCE_FILE}
    ${FCCS_INCLUDE_FILE}
)

target_include_directories(SmartFCCS PUBLIC ${FCCS_INCLUDE_DIRECTION})
target_compile_definitions(SmartFCCS PRIVATE UNICODE FCCS_LIBRARY)
target_link_libraries(SmartFCCS PRIVATE d3d11)
#target_precompile_headers(SmartFCCS PRIVATE pch.h)
#target_compile_options(SmartFCCS PRIVATE /wd4005 /wd26812)