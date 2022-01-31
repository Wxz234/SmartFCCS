set(FCCS_INCLUDE_DIRECTION 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/thirdparty/dxc/inc
    ${PROJECT_SOURCE_DIR}/thirdparty/d3dx12/inc
)
set(FCCS_INCLUDE_FILE 
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/SmartFCCS.h
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/Core.h
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/RHI.h
    ${PROJECT_SOURCE_DIR}/include/SmartFCCS/Window.h
)

set(FCCS_SOURCE_FILE
    device.cpp
    cmd.cpp
    window.cpp
    dx12_backend.cpp
    SmartFCCS.cpp
)

add_library(SmartFCCS SHARED 
    ${FCCS_SOURCE_FILE}
    ${FCCS_INCLUDE_FILE}
)

target_include_directories(SmartFCCS PUBLIC ${FCCS_INCLUDE_DIRECTION})
target_compile_definitions(SmartFCCS PRIVATE UNICODE FCCS_LIBRARY)
target_link_libraries(SmartFCCS PRIVATE d3d12 d3dcompiler dxguid dxgi)