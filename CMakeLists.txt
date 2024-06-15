cmake_minimum_required(VERSION 3.5)

project(wxMinesweeper LANGUAGES CXX)

add_subdirectory(libs/wxWidgets-3.2.4)
add_executable(wxMinesweeper field.cpp field.h minesweeper.cpp minesweeper.h)
target_link_libraries(wxMinesweeper wx::net wx::core wx::base)