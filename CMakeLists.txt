# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.16)

# Define your project name
project(minesweeper VERSION 1.0 LANGUAGES CXX)

# Set build options for wxWidgets
set(wxBUILD_SHARED OFF)  # Use static wxWidgets libraries

# Ensure that git submodules are updated before proceeding
execute_process(
  COMMAND git submodule update --init --recursive
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE result
)

if(result)
    message(FATAL_ERROR "Git submodule update failed!")
endif()

# Add the wxWidgets submodule as a subdirectory
add_subdirectory(external/wxWidgets)

# Add your application executable
add_executable(minesweeper minesweeper.cpp field.cpp)

# Link your application with wxWidgets libraries
target_link_libraries(minesweeper PRIVATE wx::net wx::core wx::base)

# Set C++ standard
target_compile_features(minesweeper PRIVATE cxx_std_17)

# Include directories for your source files
target_include_directories(minesweeper PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Handle the build system for cross-platform compatibility
if(NOT EXISTS "${CMAKE_BINARY_DIR}/CMakeCache.txt")
    message(STATUS "Creating the 'build' directory and running cmake ..")

    # Create the build directory
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}"
    )
    
    # Run cmake .. for configuration
    execute_process(
        COMMAND ${CMAKE_COMMAND} ..
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # Build based on platform
    if(WIN32)
        # Use Visual Studio or another build tool for Windows
        message(STATUS "Building with MSBuild on Windows")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Release
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    elseif(APPLE)
        # Use Xcode on macOS
        message(STATUS "Building with Xcode on macOS")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Release
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    else()
        # Default to make for Linux and others
        message(STATUS "Building with Make on Linux or other Unix-like systems")
        execute_process(
            COMMAND make
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
else()
    message(STATUS "CMakeCache.txt exists, skipping the automatic build")
endif()
