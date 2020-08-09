cmake_minimum_required(VERSION 3.15)
project(homophily_structural_balance)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -Wall -Wshadow -Wunused -pedantic -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Ofast -pthread ")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wshadow -Wunused -pedantic -pthread -Wextra")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*")

add_executable(homophily_structural_balance "${source_files}" src/Simulation.h src/Utils.h src/Metrics.h)

