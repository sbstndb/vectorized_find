#include <benchmark/benchmark.h>

#include <iostream>
#include <immintrin.h>


const int MS = 2 ; // Min_size of arrays
const int RM = 2 ; /// RangeMultiplier
const int PS = 12 ; // pow size


int naive_find(int* vector, int size, int value){
	int index = -1 ;
        for (int i = 0 ; i < size ; i++){
                if (vector[i] == value){
                        index = i ;
                        return index;
                }
        }
	return index ; 
}



int nobreak_find(int* vector, int size, int value){
        int index = -1 ;
        for (int i = 0 ; i < size ; i++){
                if (vector[i] == value){
                        index = i ;
			// Note : work if we do not have twice the value. 
			// If the array is sorted, you can travel the vector 
			// 	backwards and then get the first value
                }
        }
        return index ;
}




int intrinsic_find(int* vector, int size, int value){
	// experimental
	int index = -1 ; 
	__m256i target = _mm256_set1_epi32(value) ; 

	for (int i = 0 ; i < size ; i+=8){//avx2
		__m256i chunk = _mm256_loadu_si256((const __m256i_u*)&vector[i]); // load vector in AVX reg
		__m256i cmp = _mm256_cmpeq_epi32(chunk, target);
		int mask_result = _mm256_movemask_epi8(cmp);
		if (mask_result !=0){
			int index = __builtin_ctz(mask_result) / 4 ; 
			return i+index ; 
		}
	}
	return index ;
}


void init_vector(int* vector, int size, int value, int index){
        for (int i = 0 ; i < size ; i++){
                vector[i] = 0 ;
        }
	vector[index] = value ;
}



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

/**

int main(){
	int size = 8*256; 
	int* vector = (int*) malloc(sizeof(int) * size) ; 

	int value = 1 ; 

	init_vector(vector, size, value, size-1) ; 
			//
	int naive_index = naive_find(vector, size, value);
	std::cout << "Index : " << naive_index << std::endl ; 

        int nobreak_index = nobreak_find(vector, size, value);
        std::cout << "Index : " << nobreak_index << std::endl ;


        int intrinsic_index = intrinsic_find(vector, size, value);
        std::cout << "Index : " << intrinsic_index << std::endl ;
}
**/


BENCHMARK(BM_NaiveFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_NoBreakFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);
BENCHMARK(BM_IntrinsicFind)->RangeMultiplier(RM)->Range(MS << 0, 1 << PS);




BENCHMARK_MAIN() ; 


