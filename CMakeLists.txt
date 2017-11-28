# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(3dpp)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# Executable
add_executable(3dpp main.cpp)

# Libs
# On Mac:
#   brew install glew
#   brew install sdl
#   brew install glm

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${SDL_INCLUDE_DIRS})

target_link_libraries(3dpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SDL_LIBRARY})
