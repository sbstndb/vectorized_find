#include <benchmark/benchmark.h>
#include <iostream>
#include <immintrin.h>

#include "find.hpp"


const int MS = 2 ; // Min_size of arrays
const int RM = 2 ; /// RangeMultiplier
const int PS = 12 ; // pow size


void BM_NaiveFind(benchmark::State& state){
	const int size = state.range(0) ; 
	int* vector = (int*) malloc(sizeof(int) * size) ;
	int value = 1 ; 
	init_vector(vector, size, value, size-1);
	int index ; 
	for (auto _ : state){
		index = naive_find(vector, size, value);
		benchmark::DoNotOptimize(index);
	}
	state.SetItemsProcessed(state.iterations() * size);	
	free(vector);
}

void BM_NoBreakFind(benchmark::State& state){
        const int size = state.range(0) ;
        int* vector = (int*) aligned_alloc(64, sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = nobreak_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
	state.SetItemsProcessed(state.iterations() * size);	
	free(vector);
}


void BM_CompareFind(benchmark::State& state){
        const int size = state.range(0) ;
        int* vector = (int*) aligned_alloc(64, sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = compare_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
        free(vector);
}

void BM_CompareFloatFind(benchmark::State& state){
        const int size = state.range(0) ;
        float* vector = (float*) aligned_alloc(64, sizeof(float) * size) ;
        float value = 1.0f ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = compare_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
        free(vector);
}




void BM_CppFind(benchmark::State& state){
        const int size = state.range(0) ;
        int* vector = (int*) aligned_alloc(64, sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = cpp_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
	free(vector);
}

void BM_CppVectorFind(benchmark::State& state){
        const int size = state.range(0) ;
	std::vector<int> vector(size, 0) ; 
        int value = 1 ;
	vector[size-1] = value ; 
	int index = -1 ; 
        for (auto _ : state){
                index = cppvector_find(vector, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
}

void BM_IntrinsicFind(benchmark::State& state){
        int size = state.range(0) ;
	// !! AVX 
	if (size < 8) {
		size = 8 ; 
	}
        int* vector = (int*) malloc(sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = intrinsic_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
	state.SetItemsProcessed(state.iterations() * size);
	free(vector);
}

void BM_IntrinsicFloatFind(benchmark::State& state){
        int size = state.range(0) ;
        // !! AVX 
        if (size < 8) {
                size = 8 ;
        }
        float* vector = (float*) malloc(sizeof(float) * size) ;
        float value = 1.0f ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = intrinsic_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
        free(vector);
}



void BM_Intrinsic2Find(benchmark::State& state){
        int size = state.range(0) ;
        // !! AVX
        if (size < 8) {
                size = 8 ;
        }
        int* vector = (int*) malloc(sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        for (auto _ : state){
                index = intrinsic2_find(vector, size, value);
                benchmark::DoNotOptimize(index);
        }
        state.SetItemsProcessed(state.iterations() * size);
        free(vector);
}


BENCHMARK(BM_NaiveFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_NoBreakFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_CompareFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_CompareFloatFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_CppFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_CppVectorFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_IntrinsicFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_IntrinsicFloatFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_Intrinsic2Find)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);





BENCHMARK_MAIN() ; 


