include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${THIRDPARTY_BASE_DIR})

set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_VERSION 0.15.1)

if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD https://raw.githubusercontent.com/TheLartians/CPM.cmake/v${CPM_VERSION}/cmake/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})

include(${CPM_DOWNLOAD_LOCATION})


##################################################
# GLFW
##################################################

CPMAddPackage(
  NAME glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.2
  DOWNLOAD_ONLY True
  OPTIONS
  "GLFW_INSTALL OFF"
  "GLFW_BUILD_DOCS OFF"
  "GLFW_BUILD_TESTS OFF"
  "GLFW_BUILD_EXAMPLES OFF"
)


##################################################
# GLEW
##################################################

CPMAddPackage(
  NAME glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.1.0
  DOWNLOAD_ONLY True
  OPTIONS
  "glew-cmake_BUILD_SHARED OFF"
)

##################################################
# GLM
##################################################

CPMAddPackage(
  NAME glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.5
  DOWNLOAD_ONLY True
)

##################################################
# stduuid
##################################################

CPMAddPackage(
  NAME stduuid
  GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
  GIT_TAG v1.0
  DOWNLOAD_ONLY True
)
	

##################################################
# Assimp
##################################################

CPMAddPackage(
  NAME assimp
  GIT_REPOSITORY git@github.com:assimp/assimp.git
  GIT_TAG v5.0.0
  DOWNLOAD_ONLY True
  OPTIONS
  "ASSIMP_BUILD_TESTS OFF"
  "ASSIMP_BUILD_ASSIMP_TOOLS OFF"
)

##################################################
# Imgui
##################################################

CPMAddPackage(
  NAME imgui
  GIT_REPOSITORY git@github.com:ocornut/imgui.git
  GIT_TAG v1.74
  LOAD_ONLY True
)

##################################################
# Catch2
##################################################

CPMAddPackage(
  NAME catch2
  GIT_REPOSITORY git@github.com:catchorg/Catch2.git
  GIT_TAG v2.11.1
  DOWNLOAD_ONLY True
)
if(catch2_ADDED)
	list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
endif()

##################################################
# Loguru
##################################################

CPMAddPackage(
  NAME loguru
  GIT_REPOSITORY git@github.com:emilk/loguru.git
  GIT_TAG v2.1.0
  DOWNLOAD_ONLY True
)