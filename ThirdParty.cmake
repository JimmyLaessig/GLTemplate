include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${THIRDPARTY_BASE_DIR})

##################################################
# GLFW
##################################################

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  message(STATUS "Cloning glfw: https://github.com/glfw/glfw.git")
  FetchContent_Populate(glfw)
  message(STATUS "Cloning glfw: https://github.com/glfw/glfw.git - done")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )


##################################################
# GLEW
##################################################

FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG glew-cmake-2.1.0
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
  message(STATUS "Cloning glew: https://github.com/Perlmint/glew-cmake.git")
  FetchContent_Populate(glew)
 message(STATUS "Cloning glew: https://github.com/Perlmint/glew-cmake.git - done")
endif()


##################################################
# GLM
##################################################

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.5
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  message(STATUS "Cloning glm:  https://github.com/g-truc/glm.git")
  FetchContent_Populate(glm)
  message(STATUS "Cloning glm:  https://github.com/g-truc/glm.git - done")
endif()

##################################################
# stduuid
##################################################

FetchContent_Declare(
  stduuid
  GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
  GIT_TAG v1.0
)

FetchContent_GetProperties(stduuid)
if(NOT stduuid_POPULATED)
  message(STATUS "Cloning stduuid:  https://github.com/mariusbancila/stduuid.git")
  FetchContent_Populate(stduuid)
  message(STATUS "Cloning stduuid:  https://github.com/mariusbancila/stduuid.git - done")
endif()
	

##################################################
# Assimp
##################################################

FetchContent_Declare(
  assimp
  GIT_REPOSITORY git@github.com:assimp/assimp.git
  GIT_TAG v5.0.0
)

FetchContent_GetProperties(assimp)
if(NOT assimp_POPULATED)
  message(STATUS "Cloning assimp:  git@github.com:assimp/assimp.git")
  FetchContent_Populate(assimp)
  message(STATUS "Cloning assimp:  git@github.com:assimp/assimp.git - done")
endif()


##################################################
# Imgui
##################################################

FetchContent_Declare(
  imgui
  GIT_REPOSITORY git@github.com:ocornut/imgui.git
  GIT_TAG v1.74
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  message(STATUS "Cloning imgui:  git@github.com:ocornut/imgui.git")
  FetchContent_Populate(imgui)
  message(STATUS "Cloning imgui:  git@github.com:ocornut/imgui.git - done")
endif()


