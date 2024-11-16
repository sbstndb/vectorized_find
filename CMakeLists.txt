cmake_minimum_required(VERSION 3.28)

project(VectorizedFind LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -Ofast ")


find_package(benchmark REQUIRED)

# Ajouter le fichier de benchmark

include_directories(include)

add_executable(naive src/naive.cpp)
add_executable(nobreak src/nobreak.cpp)
add_executable(intrinsic src/intrinsic.cpp)

add_executable(benchmark_find src/benchmark.cpp)
target_link_libraries(benchmark_find PRIVATE benchmark::benchmark)

