cmake_minimum_required(VERSION 3.3)

set(PROJECT Example)
project(${PROJECT})


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


add_executable(${PROJECT} ${SOURCES})


set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)


#target_include_directories(${PROJECT} PUBLIC
#    
#)

set(LIBRARIES
    GLTemplate
)

target_link_libraries(${PROJECT} ${LIBRARIES})