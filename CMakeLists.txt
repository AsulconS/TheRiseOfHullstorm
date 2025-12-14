cmake_minimum_required(VERSION 4.0...4.2)

# Project info
project(troh VERSION 1.0.0 LANGUAGES C CXX)

# Project options
option(BUILD_SHARED_LIBS "Build in shared mode [Shared by default]." ON)

# Set where runtime files should go
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}>/bin/$<IF:$<CONFIG:Debug>,Debug,Release>)

include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.2
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG v6.0.2
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)

set(GLM_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glm)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

add_custom_target(copy_shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
)
add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

add_executable(troh src/main.cpp external/src/glad/glad.c)
add_dependencies(troh copy_shaders copy_assets)
target_include_directories(troh PRIVATE include external/include)
target_compile_features(troh PRIVATE cxx_std_20)
target_link_libraries(troh PRIVATE glm::glm glfw assimp)

# Packaging
include(GNUInstallDirs)
install(TARGETS troh RUNTIME DESTINATION bin)
install(TARGETS glfw assimp RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/ DESTINATION bin/shaders)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/ DESTINATION bin/res)

set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

include(CPack)
