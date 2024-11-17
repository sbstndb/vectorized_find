#include <immintrin.h>
#include <algorithm>
#include <vector>


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


int cpp_find(int* vector, int size, int value){
	int *pindex = std::find(vector, vector + size, value) ; 
	// Theorically, we have to verify vector[pindex] == value ...
	return pindex - vector ; 
}


int cppvector_find(std::vector<int>& vector, int value){
        auto aindex = std::find(vector.begin(), vector.end(), value) ;
        // Theorically, we have to verify vector[pindex] == value ...
        return std::distance (vector.begin(), aindex) ;
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

