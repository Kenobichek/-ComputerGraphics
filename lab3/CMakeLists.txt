# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.9)

project ("lab3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Include sub-projects.
add_subdirectory ("lab3")

find_package(OpenGL REQUIRED)

#Adding external CMakeList.txt files
add_subdirectory(lib/glm)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/assimp)

# Look up GLM
#find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIRS})

#add GLEW as STATIC library
add_library(GLEW STATIC lib/glew/src/glew.c lib/glew/include/GL/glew.h)


include_directories(
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        lib/glfw/include/
                        lib/glew/include/
                        lib/glm/
                        lib/glad/
                        lib/assimp/include/  
                    )

# set variables that are needed
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
