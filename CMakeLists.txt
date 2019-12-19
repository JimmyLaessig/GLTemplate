cmake_minimum_required(VERSION 3.3)

set(PROJECT GLTemplate)
project(${PROJECT})


set(THIRDPARTY_BASE_DIR ${PROJECT_SOURCE_DIR}/thirdParty)
### dependencies
include(ThirdParty.cmake)


find_package(OpenGL REQUIRED)

### build target 
set (SOURCES
        src/main.cpp
	)


add_executable(${PROJECT} ${SOURCES})

add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})

target_include_directories(${PROJECT} PUBLIC
    include
	${glfw_SOURCE_DIR}/include/GLFW
	${glew_SOURCE_DIR}/include
	${glm_SOURCE_DIR}
)


set(LIBRARIES
    glfw
    ${GLFW_LIBRARIES}
    libglew_static
    OpenGL32
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