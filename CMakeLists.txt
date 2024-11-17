cmake_minimum_required(VERSION 3.28)

project(VectorizedFind LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


# options de compilations en fonction du toolchain
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message(STATUS "Detected GCC compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -Ofast -g")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message(STATUS "Detected Clang compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -O3 -fvectorize -ffast-math -funroll-loops -fslp-vectorize -mllvm -vectorize-loops -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize  -g") # no longuer Ofast in modern clang++
else()
	message(STATUS "Unknown Compiler : ${CMAKE_CXX8COMPILER_ID}")
	message(STATUS "Select non-custom compilation flags")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -Ofast -g")	
endif()


find_package(benchmark REQUIRED)

# Ajouter le fichier de benchmark

include_directories(include)

add_executable(naive src/naive.cpp)
add_executable(nobreak src/nobreak.cpp)
add_executable(intrinsic src/intrinsic.cpp)

add_executable(benchmark_find src/benchmark.cpp)
target_link_libraries(benchmark_find PRIVATE benchmark::benchmark)

