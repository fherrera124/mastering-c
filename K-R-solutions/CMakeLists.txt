cmake_minimum_required(VERSION 3.22.1)

project(k-R)

# Build information
message(STATUS "Build Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build executables in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Source directories
set(CH03_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ch03)

# Create the executables
add_executable(ex3_1 ${CH03_DIR}/ex3_1.c)
add_executable(ex3_2 ${CH03_DIR}/ex3_2.c)
add_executable(ex3_3 ${CH03_DIR}/ex3_3.c)
add_executable(ex3_4 ${CH03_DIR}/ex3_4.c)
add_executable(ex3_5 ${CH03_DIR}/ex3_5.c)
add_executable(ex3_6 ${CH03_DIR}/ex3_6.c)

# Add subdirectory to the build
add_subdirectory(utils)

# Linkg library to executables
target_link_libraries(ex3_4 utils)
target_link_libraries(ex3_5 utils)
target_link_libraries(ex3_6 utils)

# Include directory to executables (for header files)
target_include_directories(ex3_4 PRIVATE utils)
target_include_directories(ex3_5 PRIVATE utils)
target_include_directories(ex3_6 PRIVATE utils)