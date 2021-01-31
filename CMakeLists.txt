cmake_minimum_required(VERSION 3.15)

project(GLTemplate)

include(cmake/ShaderCompiler.cmake)

include(cmake/Conan.cmake)

conan_install()

message(WARNING ${DXC_EXECUTABLE} )
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(GLTemplate)
add_subdirectory(example)
add_subdirectory(test)


#set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
#include(ThirdParty.cmake)


#set_target_properties("libglew_static" PROPERTIES FOLDER "glew")
#set_target_properties("libglewmx_static" PROPERTIES FOLDER "glew")
#set_target_properties("assimp" PROPERTIES FOLDER "assimp")
#set_target_properties("IrrXML" PROPERTIES FOLDER "assimp")
#set_target_properties("UpdateAssimpLibsDebugSymbolsAndDLLs" PROPERTIES FOLDER "assimp")
#set_target_properties("zlib" PROPERTIES FOLDER "assimp")
#set_target_properties("zlibstatic" PROPERTIES FOLDER "assimp")