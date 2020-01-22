cmake_minimum_required(VERSION 3.3)

set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
include(ThirdParty.cmake)


set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})

add_subdirectory(GLTemplate)
add_subdirectory(example)
add_subdirectory(test)

set_target_properties("libglew_static" PROPERTIES FOLDER "glew")
set_target_properties("libglewmx_static" PROPERTIES FOLDER "glew")
set_target_properties("assimp" PROPERTIES FOLDER "assimp")
set_target_properties("IrrXML" PROPERTIES FOLDER "assimp")
set_target_properties("UpdateAssimpLibsDebugSymbolsAndDLLs" PROPERTIES FOLDER "assimp")
set_target_properties("zlib" PROPERTIES FOLDER "assimp")
set_target_properties("zlibstatic" PROPERTIES FOLDER "assimp")