# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build

# Include any dependencies generated for this target.
include NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/depend.make

# Include the progress variables for this target.
include NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/progress.make

# Include the compile flags for this target's objects.
include NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o: ../NFComm/NFConfigPlugin/dllmain.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NFConfigPlugin.dir/dllmain.o -c /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/dllmain.cpp

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NFConfigPlugin.dir/dllmain.i"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/dllmain.cpp > CMakeFiles/NFConfigPlugin.dir/dllmain.i

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NFConfigPlugin.dir/dllmain.s"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/dllmain.cpp -o CMakeFiles/NFConfigPlugin.dir/dllmain.s

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.requires:
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.provides: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.requires
	$(MAKE) -f NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.provides.build
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.provides

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.provides.build: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o: ../NFComm/NFConfigPlugin/myrc4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NFConfigPlugin.dir/myrc4.o -c /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/myrc4.cpp

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NFConfigPlugin.dir/myrc4.i"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/myrc4.cpp > CMakeFiles/NFConfigPlugin.dir/myrc4.i

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NFConfigPlugin.dir/myrc4.s"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/myrc4.cpp -o CMakeFiles/NFConfigPlugin.dir/myrc4.s

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.requires:
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.provides: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.requires
	$(MAKE) -f NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.provides.build
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.provides

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.provides.build: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o: ../NFComm/NFConfigPlugin/NFCClassModule.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o -c /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCClassModule.cpp

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NFConfigPlugin.dir/NFCClassModule.i"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCClassModule.cpp > CMakeFiles/NFConfigPlugin.dir/NFCClassModule.i

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NFConfigPlugin.dir/NFCClassModule.s"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCClassModule.cpp -o CMakeFiles/NFConfigPlugin.dir/NFCClassModule.s

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.requires:
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.provides: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.requires
	$(MAKE) -f NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.provides.build
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.provides

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.provides.build: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o: ../NFComm/NFConfigPlugin/NFCElementModule.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o -c /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCElementModule.cpp

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NFConfigPlugin.dir/NFCElementModule.i"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCElementModule.cpp > CMakeFiles/NFConfigPlugin.dir/NFCElementModule.i

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NFConfigPlugin.dir/NFCElementModule.s"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFCElementModule.cpp -o CMakeFiles/NFConfigPlugin.dir/NFCElementModule.s

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.requires:
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.provides: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.requires
	$(MAKE) -f NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.provides.build
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.provides

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.provides.build: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/flags.make
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o: ../NFComm/NFConfigPlugin/NFConfigPlugin.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o -c /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFConfigPlugin.cpp

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.i"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFConfigPlugin.cpp > CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.i

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.s"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin/NFConfigPlugin.cpp -o CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.s

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.requires:
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.provides: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.requires
	$(MAKE) -f NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.provides.build
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.provides

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.provides.build: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o

# Object files for target NFConfigPlugin
NFConfigPlugin_OBJECTS = \
"CMakeFiles/NFConfigPlugin.dir/dllmain.o" \
"CMakeFiles/NFConfigPlugin.dir/myrc4.o" \
"CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o" \
"CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o" \
"CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o"

# External object files for target NFConfigPlugin
NFConfigPlugin_EXTERNAL_OBJECTS =

../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build.make
../_Out/Release/NFConfigPlugin.so: ../_Out/Release/NFCore.so
../_Out/Release/NFConfigPlugin.so: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../../_Out/Release/NFConfigPlugin.so"
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NFConfigPlugin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build: ../_Out/Release/NFConfigPlugin.so
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/build

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/dllmain.o.requires
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/myrc4.o.requires
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCClassModule.o.requires
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFCElementModule.o.requires
NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires: NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/NFConfigPlugin.o.requires
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/requires

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/clean:
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin && $(CMAKE_COMMAND) -P CMakeFiles/NFConfigPlugin.dir/cmake_clean.cmake
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/clean

NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/depend:
	cd /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/NFComm/NFConfigPlugin /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin /mnt/hgfs/OSP/NoahGameFrame-Develop/NoahGameFrame/build/NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : NFComm/NFConfigPlugin/CMakeFiles/NFConfigPlugin.dir/depend

