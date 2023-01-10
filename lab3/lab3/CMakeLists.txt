# CMakeList.txt : CMake project for lab3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# Add source to this project's executable.
file(GLOB lab3_files "*.h" "*.cpp")

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res" SYMBOLIC)

add_executable(lab3 ${lab3_files})

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm glad assimp GLEW glfw ${GLFW_LIBRARIES})
