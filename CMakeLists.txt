cmake_minimum_required(VERSION 3.3)

set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
include(ThirdParty.cmake)


set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



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