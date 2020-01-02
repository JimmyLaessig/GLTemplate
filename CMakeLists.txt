cmake_minimum_required(VERSION 3.3)

set(PROJECT GLTemplate)
project(${PROJECT})


set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
include(ThirdParty.cmake)


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


add_executable(${PROJECT} ${SOURCES})

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)



add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})

target_include_directories(${PROJECT} PUBLIC
    include
	${glfw_SOURCE_DIR}/include/GLFW
	${glew_SOURCE_DIR}/include
	${assimp_SOURCE_DIR}/include
    	${glm_SOURCE_DIR}
    	${imgui_SOURCE_DIR}
)


set(LIBRARIES
    glfw
    ${GLFW_LIBRARIES}
    libglew_static
    OpenGL32
	assimp
)
target_link_libraries(${PROJECT} ${LIBRARIES})

#add_custom_command(TARGET ${PROJECT} POST_BUILD        
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different  		
#        ${CMAKE_CURRENT_BINARY_DIR}/bin/glewd.dll
#        ${CMAKE_CURRENT_BINARY_DIR}/glewd.dll)



#add_custom_command(TARGET ${PROJECT} POST_BUILD        
#   COMMAND ${CMAKE_COMMAND} -E copy_if_different  		
#        ${glfw_BINARY_DIR}/src/glfw3.dll
#        ${CMAKE_CURRENT_BINARY_DIR}/glfw3.dll)


#INSTALL( TARGETS ${PROJECT} ARCHIVE DESTINATION lib#
#		                    LIBRARY DESTINATION lib
#                            RUNTIME DESTINATION bin )
                                        
#set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "default install prefix" FORCE)

#install(CODE "file(REMOVE_RECURSE ${CMAKE_INSTALL_PREFIX}/*)")
#install(TARGETS ${PROJECT} RUNTIME DESTINATION lib LIBRARY DESTINATION lib)
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/license DESTINATION .)

#install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)
#install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION .)