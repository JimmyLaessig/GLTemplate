

set(TARGET_NAME EngineName)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE BASE_PUBLIC_INC CONFIGURE_DEPENDS "include/Base/*.h")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE BASE_SRC CONFIGURE_DEPENDS "src/Base/*.cpp")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE BASE_PRIVATE_INC CONFIGURE_DEPENDS "src/Base/*.h")


# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE RENDERING_PUBLIC_INC CONFIGURE_DEPENDS "include/Rendering/*.h")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE RENDERING_SRC CONFIGURE_DEPENDS "src/Rendering/*.cpp")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE RENDERING_PRIVATE_INC CONFIGURE_DEPENDS "src/Rendering/*.h")


# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE APPLICATION_PUBLIC_INC CONFIGURE_DEPENDS "include/Application/*.h")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE APPLICATION_SRC CONFIGURE_DEPENDS "src/Application/*.cpp")

# Whenever this glob's value changes, cmake will rerun and update the build with the
# new/removed files.
file(GLOB_RECURSE APPLICATION_PRIVATE_INC CONFIGURE_DEPENDS "src/Application/*.h")


add_library(${TARGET_NAME}
    ${BASE_PUBLIC_INC}
	${BASE_SRC}
	${BASE_PRIVATE_INC}
    ${RENDERING_PUBLIC_INC}
	${RENDERING_SRC}
	${RENDERING_PRIVATE_INC}
	${APPLICATION_PUBLIC_INC}
	${APPLICATION_SRC}
	${APPLICATION_PRIVATE_INC}
)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BASE_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BASE_PRIVATE_INC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BASE_PUBLIC_INC})
                                                    
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RENDERING_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RENDERING_PRIVATE_INC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RENDERING_PUBLIC_INC})
                                                    
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APPLICATION_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APPLICATION_PRIVATE_INC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APPLICATION_PUBLIC_INC})

#Set target properties
target_include_directories(${TARGET_NAME}
    PUBLIC
        include/
    #PRIVATE
        src/
)

target_link_libraries(${TARGET_NAME}
    CONAN_PKG::glm
    CONAN_PKG::glew
	CONAN_PKG::glfw
    CONAN_PKG::stduuid
    CONAN_PKG::abseil
)