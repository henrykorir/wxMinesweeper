cmake_minimum_required(VERSION 3.5)
project(wxMinesweeper LANGUAGES CXX)
find_package(wxWidgets)
if(NOT wxWidgets_FOUND)
    execute_process(COMMAND sudo apt-get install -y build-essential libgtk2.0-dev libgtk-3-dev)
    execute_process(COMMAND sudo su)
    include(ExternalProject)
    ExternalProject_Add(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
        GIT_TAG v3.2.4
        STEP_TARGETS   build
    )
    if (UNIX)
        execute_process(COMMAND sudo ln -sv wx-3.2/wx wx)
    endif (UNIX)

    if (WIN32)
        #execute_process(COMMAND sudo ln -sv wx-2.8/wx wx)
    endif (WIN32)
   
    if (MSVC)
        # do something
    endif (MSVC)
    
endif()
execute_process(COMMAND wx-config --version)
include(${wxWidgets_USE_FILE})
add_executable(wxMinesweeper field.cpp field.h minesweeper.cpp minesweeper.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
