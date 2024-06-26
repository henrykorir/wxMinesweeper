# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/freedom/Desktop/work/minesweeper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/freedom/Desktop/work/minesweeper

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/freedom/Desktop/work/minesweeper/CMakeFiles /home/freedom/Desktop/work/minesweeper//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/freedom/Desktop/work/minesweeper/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named wxMinesweeper

# Build rule for target.
wxMinesweeper: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 wxMinesweeper
.PHONY : wxMinesweeper

# fast build rule for target.
wxMinesweeper/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/build
.PHONY : wxMinesweeper/fast

field.o: field.cpp.o
.PHONY : field.o

# target to build an object file
field.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/field.cpp.o
.PHONY : field.cpp.o

field.i: field.cpp.i
.PHONY : field.i

# target to preprocess a source file
field.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/field.cpp.i
.PHONY : field.cpp.i

field.s: field.cpp.s
.PHONY : field.s

# target to generate assembly for a file
field.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/field.cpp.s
.PHONY : field.cpp.s

minesweeper.o: minesweeper.cpp.o
.PHONY : minesweeper.o

# target to build an object file
minesweeper.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/minesweeper.cpp.o
.PHONY : minesweeper.cpp.o

minesweeper.i: minesweeper.cpp.i
.PHONY : minesweeper.i

# target to preprocess a source file
minesweeper.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/minesweeper.cpp.i
.PHONY : minesweeper.cpp.i

minesweeper.s: minesweeper.cpp.s
.PHONY : minesweeper.s

# target to generate assembly for a file
minesweeper.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/wxMinesweeper.dir/build.make CMakeFiles/wxMinesweeper.dir/minesweeper.cpp.s
.PHONY : minesweeper.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... wxMinesweeper"
	@echo "... field.o"
	@echo "... field.i"
	@echo "... field.s"
	@echo "... minesweeper.o"
	@echo "... minesweeper.i"
	@echo "... minesweeper.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

