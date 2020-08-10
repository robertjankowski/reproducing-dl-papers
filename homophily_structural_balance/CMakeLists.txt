cmake_minimum_required(VERSION 3.15)
project(homophily_structural_balance)

find_package(OpenMP)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -fopenmp -Wall -Wshadow -Wunused -pedantic -Wextra")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*")

add_executable(homophily_structural_balance "${source_files}" src/Simulation.h src/Utils.h src/Metrics.h)

target_compile_options(homophily_structural_balance PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(homophily_structural_balance PRIVATE ${OpenMP_CXX_FLAGS})
