cmake_minimum_required(VERSION 3.15)
project(homophily_structural_balance)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -pedantic -pthread -Wextra") # -O3
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*")

add_executable(homophily_structural_balance "${source_files}")