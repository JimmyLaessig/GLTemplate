

set(DXC_EXECUTABLE ${CMAKE_BINARY_DIR}/build_tools/dxc_2020_10-22/bin/x64/dxc.exe)
set(SPIRV_CROSS_EXECUTABLE ${CMAKE_BINARY_DIR}/build_tools/spirv-cross-vs2017-64bit-8891bd3512/bin/spirv-cross.exe)


if (NOT EXISTS "${DXC_EXECUTABLE}")
    file(DOWNLOAD
        https://github.com/microsoft/DirectXShaderCompiler/releases/download/v1.5.2010/dxc_2020_10-22.zip
        ${CMAKE_BINARY_DIR}/build_tools/dxc_2020_10-22.zip
        SHOW_PROGRESS
    )
      
    file(ARCHIVE_EXTRACT 
        INPUT ${CMAKE_BINARY_DIR}/build_tools/dxc_2020_10-22.zip
        DESTINATION ${CMAKE_BINARY_DIR}/build_tools/dxc_2020_10-22
    )

endif()

if (NOT EXISTS "${SPIRV_CROSS_EXECUTABLE}")
    file(DOWNLOAD
        https://github.com/KhronosGroup/SPIRV-Cross/releases/download/2020-09-17/spirv-cross-vs2017-64bit-8891bd3512.tar.gz
        ${CMAKE_BINARY_DIR}/build_tools/spirv-cross-vs2017-64bit-8891bd3512.tar.gz
        SHOW_PROGRESS
    )

    file(ARCHIVE_EXTRACT 
        INPUT ${CMAKE_BINARY_DIR}/build_tools/spirv-cross-vs2017-64bit-8891bd3512.tar.gz
        DESTINATION ${CMAKE_BINARY_DIR}/build_tools/spirv-cross-vs2017-64bit-8891bd3512
    )

endif()

#file(DOWNLOAD
#    https://github.com/KhronosGroup/SPIRV-Cross/releases/download/2020-09-17/spirv-cross-vs2017-64bit-8891bd3512.tar.gz
#    ${CMAKE_BINARY_DIR}
#)

#file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/spirv-cross-vs2017-64bit-8891bd3512.tar.gz)