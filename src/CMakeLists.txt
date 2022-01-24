set(FCCS_INCLUDE_DIRECTION 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/thirdparty/dxc/inc
    ${PROJECT_SOURCE_DIR}/thirdparty/d3dx12/inc
)
set(FCCS_INCLUDE_FILE 
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/SmartFCCS.h
)

set(FCCS_SOURCE_FILE
    device.cpp
    thirdparty.cpp
    dx12_backend.cpp
    SmartFCCS.cpp
)

add_library(SmartFCCS STATIC 
    ${FCCS_SOURCE_FILE}
    ${FCCS_INCLUDE_FILE}
)

target_include_directories(SmartFCCS PUBLIC ${FCCS_INCLUDE_DIRECTION})
target_compile_definitions(SmartFCCS PRIVATE UNICODE)