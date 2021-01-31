
cmake_minimum_required(VERSION 3.3)
include(GNUInstallDirs)

set(TARGET_NAME Example)


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
)

add_executable(${TARGET_NAME} ${SOURCES})

set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")

#find_package(EngineName REQUIRED)

target_link_libraries(${TARGET_NAME} EngineName)

#find_package(Common CONFIG REQUIRED)
#message(ERROR ${Common_LIBRARIES})
#set(LIBRARIES
#    ${Common_LIBRARIES}
#)

#target_include_directories(${LIBRARY_NAME} PRIVATE#
#	${Common_INCLUDE_DIRS}
#)

#target_link_libraries(${LIBRARY_NAME} ${LIBRARIES})


#add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD        
#   COMMAND ${CMAKE_COMMAND} -E copy_directory		#
#	${CMAKE_SOURCE_DIR}/Assets/
#	$<TARGET_FILE_DIR:Example>/Assets/)