cmake_minimum_required(VERSION 3.5)

set(PROJECT GLTemplateTests)
project(${PROJECT})


set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "" FORCE)
add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT} ${sources})

#find_package(Catch2 REQUIRED)
target_include_directories(${PROJECT} PUBLIC
    ../include
    ${catch2_SOURCE_DIR}
)

target_link_libraries(${PROJECT} 
    Catch2::Catch2 
    GLTemplate
)

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT})


