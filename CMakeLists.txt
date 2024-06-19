cmake_minimum_required(VERSION 3.5)

project(wxMinesweeper LANGUAGES CXX)

# set(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
#   OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE SETUID SETGID
#    )
#    execute_process(
#     COMMAND sudo mkdir -p /usr/local/include/wx-3.2/
#     RESULT_VARIABLE mkdir_result
# )

# if(mkdir_result EQUAL 0)
#     message("Directory created successfully or already exists.")
# else()
#     message("Failed to create directory.")
# endif()

# include(ExternalProject)
# ExternalProject_Add(wxwidgets
#   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
#   GIT_TAG        v3.2.4
#   STEP_TARGETS   build
# )
aux_source_directory(. SRC_LIST)

# Copy images to the binary directory during build

file(COPY 
    ${PROJECT_SOURCE_DIR}/logo.png 
    ${PROJECT_SOURCE_DIR}/mine.png
    ${PROJECT_SOURCE_DIR}/clock.xpm
    ${PROJECT_SOURCE_DIR}/red-flag.png
    DESTINATION ${CMAKE_BINARY_DIR}
)

#find_package(wxWidgets REQUIRED COMPONENTS net core base)
#if(wxWidgets_USE_FILE) # not defined in CONFIG mode
#    include(${wxWidgets_USE_FILE})
#endif()
# add_executable(${PROJECT_NAME} ${SRC_LIST})
# target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
set(wxBUILD_MONOLITHIC OFF)

add_subdirectory(wxWidgets)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}  wx::net wx::core wx::base wx::xrc wx::qa wx::gl wx::xml)

# List all files in the current directory
file(GLOB CURRENT_DIR_CONTENTS build)

# Print out each file found
foreach(FILE ${CURRENT_DIR_CONTENTS})
    message("File found: ${FILE}")
endforeach()

foreach(FILE ${PROJECT_BINARY_DIR})
    message("File found: ${FILE}")
endforeach()
