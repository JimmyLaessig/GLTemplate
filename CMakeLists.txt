cmake_minimum_required(VERSION 3.3)

set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
include(ThirdParty.cmake)


set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)

add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
add_subdirectory(GLTemplate)
add_subdirectory(example)
add_subdirectory(test)