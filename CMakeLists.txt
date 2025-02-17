# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.16)

# Define your project name
project(minesweeper VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check for wxWidgets
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/external/wxWidgets")
    message(FATAL_ERROR "wxWidgets submodule is not initialized. Run 'git submodule update --init --recursive'.")
endif()

# Add the wxWidgets submodule as a subdirectory
add_subdirectory(external/wxWidgets)

# Add your application executable
add_executable(minesweeper minesweeper.cpp field.cpp)

# Link your application with wxWidgets libraries
target_link_libraries(minesweeper PRIVATE wx::net wx::core wx::base)

# Include directories for your source files
target_include_directories(minesweeper PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(CTest)

add_test(
    NAME Minesweeper_Run_Test
    COMMAND $<TARGET_FILE:minesweeper>
)
set_tests_properties(Minesweeper_Run_Test PROPERTIES PASS_REGULAR_EXPRESSION ".*")

