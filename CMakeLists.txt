cmake_minimum_required(VERSION 3.5)

project(wxMinesweeper LANGUAGES CXX)

set(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
     OWNER_READ
     OWNER_WRITE
     OWNER_EXECUTE
     GROUP_READ
   )

include(ExternalProject)
ExternalProject_Add(wxwidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG        v3.2.4
  STEP_TARGETS   build
)
aux_source_directory(. SRC_LIST)
#find_package(wxWidgets REQUIRED COMPONENTS net core base)
#if(wxWidgets_USE_FILE) # not defined in CONFIG mode
#    include(${wxWidgets_USE_FILE})
#endif()
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})