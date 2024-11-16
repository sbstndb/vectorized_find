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
}


BENCHMARK(BM_NaiveFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_NoBreakFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_IntrinsicFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);




BENCHMARK_MAIN() ; 

