# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pablo/repositorioGit/ICG/assimp-4.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pablo/repositorioGit/ICG/assimp-4.1.0

# Utility rule file for Experimental.

# Include the progress variables for this target.
include test/CMakeFiles/Experimental.dir/progress.make

test/CMakeFiles/Experimental:
	cd /home/pablo/repositorioGit/ICG/assimp-4.1.0/test && /usr/bin/ctest -D Experimental

Experimental: test/CMakeFiles/Experimental
Experimental: test/CMakeFiles/Experimental.dir/build.make

.PHONY : Experimental

# Rule to build all files generated by this target.
test/CMakeFiles/Experimental.dir/build: Experimental

.PHONY : test/CMakeFiles/Experimental.dir/build

test/CMakeFiles/Experimental.dir/clean:
	cd /home/pablo/repositorioGit/ICG/assimp-4.1.0/test && $(CMAKE_COMMAND) -P CMakeFiles/Experimental.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/Experimental.dir/clean

test/CMakeFiles/Experimental.dir/depend:
	cd /home/pablo/repositorioGit/ICG/assimp-4.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pablo/repositorioGit/ICG/assimp-4.1.0 /home/pablo/repositorioGit/ICG/assimp-4.1.0/test /home/pablo/repositorioGit/ICG/assimp-4.1.0 /home/pablo/repositorioGit/ICG/assimp-4.1.0/test /home/pablo/repositorioGit/ICG/assimp-4.1.0/test/CMakeFiles/Experimental.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/Experimental.dir/depend

