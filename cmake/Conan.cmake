macro(conan_install)
  # Download conan.cmake automatically
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  #conan_add_remote(
  #  NAME
  #  bincrafters
  #  URL
  #  https://api.bintray.com/conan/bincrafters/public-conan)
  
  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    catch2/2.11.0
    glm/0.9.9.5
    fmt/6.2.0
    spdlog/1.8.1
    glew/2.1.0
    glfw/3.3.2
    stduuid/1.0
    abseil/20200923.2
    glslang/8.13.3559
    spirv-cross/20200917
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()