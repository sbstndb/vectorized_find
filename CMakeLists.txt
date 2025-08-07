cmake_minimum_required(VERSION 3.28)

project(VectorizedFind LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


# Compilation options based on toolchain
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message(STATUS "Detected GCC compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -Ofast -funroll-loops -ftree-vectorize -g")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message(STATUS "Detected Clang compiler")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -O3 -fvectorize -ffast-math -funroll-loops -fslp-vectorize -mllvm -vectorize-loops -fstrict-aliasing -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize  -g") # no longuer Ofast in modern clang++
else()
	message(STATUS "Unknown Compiler : ${CMAKE_CXX8COMPILER_ID}")
	message(STATUS "Select non-custom compilation flags")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native -mavx2 -Ofast -g")	
endif()


find_package(benchmark REQUIRED)

# Add benchmark file

include_directories(
    include
    src/utils
    src/naive
    src/compare
    src/cpp_stl
    src/intrinsics
    src/benchmarks
)

add_executable(vectorized_find
    src/utils/utils.cpp
    src/naive/naive_find.cpp
    src/compare/compare_find.cpp
    src/cpp_stl/cpp_stl_find.cpp
    src/intrinsics/intrinsic_find.cpp
    src/benchmarks/benchmarks.cpp
)
target_link_libraries(vectorized_find PRIVATE benchmark::benchmark)

