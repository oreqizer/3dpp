# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.9.4)

# Project's name
project(3dpp)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# Sources
file(GLOB SOURCES "src/*.cpp")

# Executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# C++ compiler features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Libs
# On Mac:
#   brew install glew
#   brew install sdl2
#   brew install glm

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SDL2_LIBRARIES} GLEW)
