# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()


set(TARGET_NAME Test)


# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${TARGET_NAME} ${sources})

set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${TARGET_NAME} PRIVATE
    CONAN_PKG::catch2
    EngineName
)


include(CTest)

catch_discover_tests(${TARGET_NAME})