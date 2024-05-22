cmake_minimum_required(VERSION 3.5)
project(wxMinesweeper LANGUAGES CXX)
find_package(wxWidgets)
if(NOT wxWidgets_FOUND)
    execute_process(COMMAND sudo apt-get install libwxgtk2.8-dev libwxgtk2.8-dbg)
    # execute_process(COMMAND apt install libwxgtk2.8-dbg)
    include(ExternalProject)
    ExternalProject_Add(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
        GIT_TAG v3.2.4
        STEP_TARGETS   build
    )
endif()
include(${wxWidgets_USE_FILE})
add_executable(wxMinesweeper field.cpp field.h minesweeper.cpp minesweeper.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
