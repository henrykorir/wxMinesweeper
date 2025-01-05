cmake_minimum_required(VERSION 3.16)

# Define your project name
project(minesweeper)

# Specify wxWidgets location if needed
set(wxWidgets_ROOT_DIR "/usr/local")

# Find wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets settings
include(${wxWidgets_USE_FILE})

# Add an executable target
add_executable(minesweeper minesweeper.cpp field.cpp)

# Link wxWidgets libraries
target_link_libraries(minesweeper ${wxWidgets_LIBRARIES})
