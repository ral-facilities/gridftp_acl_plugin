cmake_minimum_required (VERSION 2.8.8)

# ----------- GET TEST DEPENDENCIES -------------

# Get google test dependencies
configure_file(dependencies/gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# ------------- SPD log dependency -------------------
configure_file(dependencies/spdlog.in spdlog-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/spdlog-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/spdlog-download" )

add_subdirectory("${CMAKE_BINARY_DIR}/spdlog-src"
                 "${CMAKE_BINARY_DIR}/spdlog-build")

# --------- MAIN APPLICATION -----------
project (GridftpACLPlugin)

#version number
set (GridftpACLPlugin_VERSION_MAJOR 1)
set (GridftpACLPlugin_VERSION_MINOR 0)

#include the application source files
include_directories(framework framework/logger)

file(GLOB_RECURSE framework_src "framework/**/*.h" "framework/**/*.cpp")

#indicate the entry point for the executable
add_executable (GridftpACLPlugin main.cpp ${framework_src})

# Indicate which libraries to include during the link process.
target_link_libraries (GridftpACLPlugin spdlog)

install (TARGETS GridftpACLPlugin DESTINATION bin)


# --------- TESTS -----------
add_subdirectory(test)