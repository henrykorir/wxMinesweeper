# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.16)

# Define your project name
project(minesweeper VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the wxWidgets submodule as a subdirectory
add_subdirectory(external/wxWidgets)

# Add your application executable
add_executable(minesweeper src/minesweeper.cpp src/field.cpp)

# Link your application with wxWidgets libraries
target_link_libraries(minesweeper PRIVATE wx::net wx::core wx::base)

# Include directories for your source files
target_include_directories(minesweeper PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Ensure Git submodules are updated in CI workflows (NOT here)
if(NOT wxWidgets_FOUND)
    message(FATAL_ERROR "wxWidgets is not found. Ensure submodules are initialized.")
endif()
