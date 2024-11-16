cmake_minimum_required(VERSION 3.28)

project(VectorizedFind LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -O3")


find_package(benchmark REQUIRED)

# Ajouter le fichier de benchmark
add_executable(benchmark_find main.cpp)
target_link_libraries(benchmark_find PRIVATE benchmark::benchmark)

