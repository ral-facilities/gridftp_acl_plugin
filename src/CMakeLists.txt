cmake_minimum_required (VERSION 2.8.8)

project (GridftpACLPlugin)

#version number
set (GridftpACLPlugin_VERSION_MAJOR 1)
set (GridftpACLPlugin_VERSION_MINOR 0)

#include the subdirectory containing our libs
#add_subdirectory (Hello)
#include_directories(Hello)

#indicate the entry point for the executable
add_executable (GridftpACLPlugin main.cpp)

# Indicate which libraries to include during the link process.
target_link_libraries (GridftpACLPlugin)

install (TARGETS GridftpACLPlugin DESTINATION bin)