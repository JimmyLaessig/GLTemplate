cmake_minimum_required(VERSION 3.3)

set(PROJECT GLTemplate)
project(${PROJECT})

find_package(OpenGL REQUIRED)

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "include/*.h")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")

### build target 
set (SOURCES
	${sources} 
	${headers}
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/examples/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/examples/imgui_impl_opengl3.cpp
)


add_library(${PROJECT} STATIC ${SOURCES})


set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)


target_include_directories(${PROJECT} PUBLIC
    include
	${loguru_SOURCE_DIR}/include
	${glfw_SOURCE_DIR}/include/GLFW
	${glew_SOURCE_DIR}/include
	${assimp_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
	${stduuid_SOURCE_DIR}/include
)

set(LIBRARIES
    glfw
    libglew_static
    OpenGL32
    assimp
)

target_link_libraries(${PROJECT} ${LIBRARIES})



#INSTALL( TARGETS ${PROJECT} ARCHIVE DESTINATION lib#
#		            LIBRARY DESTINATION lib
#                            RUNTIME DESTINATION bin )

#set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "default install prefix" FORCE)

#install(CODE "file(REMOVE_RECURSE ${CMAKE_INSTALL_PREFIX}/*)")
#install(TARGETS ${PROJECT} RUNTIME DESTINATION lib LIBRARY DESTINATION lib)
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/license DESTINATION .)

#install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)
#install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)