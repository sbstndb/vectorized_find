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


int compare_find(int* vector, int size, int value){
        int index = -1 ;
        for (int i = 0 ; i < size ; i++){
		index += (vector[i] < value) ; 
        }
        return index ;
}

int compare_find(float* vector, int size, float value){
	int index = -1 ; 
        for (int i = 0 ; i < size ; i++){
                index += (vector[i] < value) ;
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

/**
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
**/


int intrinsic_find(int* vector, int size, int value){
        // experimental
        int index = -1 ;
        __m256i target = _mm256_set1_epi32(value) ;
// In my cpu : optimal unrolling around 2 SIMD finds per loop	
        for (int i = 0 ; i < size ; i+=16){//avx2
                __m256i chunk  = _mm256_loadu_si256((const __m256i_u*)&vector[i]); // load vector in AVX reg
                __m256i chunk2 = _mm256_loadu_si256((const __m256i_u*)&vector[i+8]); // load vector in AVX reg		
										      //
		__m256i cmp  = _mm256_cmpeq_epi32(chunk , target);
                __m256i cmp2 = _mm256_cmpeq_epi32(chunk2, target);

                int mask_result  = _mm256_movemask_epi8(cmp );
                int mask_result2 = _mm256_movemask_epi8(cmp2);		

                if (mask_result !=0){
                        int index = __builtin_ctz(mask_result) / 4 ;
                        return i+index ;
                }
                if (mask_result2 !=0){
                        int index = __builtin_ctz(mask_result2) / 4 ;
                        return i+index+8 ;
                }
        }
        return index ;
}



int intrinsic_find(float* vector, int size, float value){
        // experimental
        int index = -1 ;
        __m256 target = _mm256_set1_ps(value) ;
// In my cpu : optimal unrolling around 2 SIMD finds per loop   
        for (int i = 0 ; i < size ; i+=16){//avx2
                __m256 chunk  = _mm256_loadu_ps(&vector[i]); // load vector in AVX reg
                __m256 chunk2 = _mm256_loadu_ps(&vector[i+8]); // load vector in AVX reg          
                                                                                      //
                __m256 cmp  = _mm256_cmp_ps(chunk , target, _CMP_EQ_OS);
                __m256 cmp2 = _mm256_cmp_ps(chunk2, target, _CMP_EQ_OS);

                int mask_result  = _mm256_movemask_ps(cmp );
                int mask_result2 = _mm256_movemask_ps(cmp2);

                if (mask_result !=0){
                        int index = __builtin_ctz(mask_result)  ;
                        return i+index ;
                }
                if (mask_result2 !=0){
                        int index = __builtin_ctz(mask_result2) ;
                        return i+index+8 ;
                }
        }
        return index ;
}




int intrinsic2_find(int* vector, int size, int value){
        // experimental
        int index = -1 ;
        __m256i target = _mm256_set1_epi32(value) ;
	__m256i count = _mm256_setzero_si256() ; 
        __m256i count2 = _mm256_setzero_si256() ;

        for (int i = 0 ; i < size ; i+=16){//avx2
                __m256i chunk = _mm256_loadu_si256((const __m256i_u*)&vector[i]); // load vector in AVX reg
                __m256i mask = _mm256_cmpgt_epi32(target, chunk);
		__m256i ones = _mm256_and_si256(mask, _mm256_set1_epi32(1));
		count = _mm256_add_epi32(count, ones) ; 

                __m256i chunk2 = _mm256_loadu_si256((const __m256i_u*)&vector[i+8]); // load vector in AVX reg
                __m256i mask2 = _mm256_cmpgt_epi32(target, chunk2);
                __m256i ones2 = _mm256_and_si256(mask2, _mm256_set1_epi32(1));
                count2 = _mm256_add_epi32(count, ones2) ;
	}
	count = _mm256_add_epi32(count, count2) ;
	

	__m256i sum = _mm256_hadd_epi32(count, count) ; 
        sum = _mm256_hadd_epi32(sum, sum) ;	


	index = _mm256_extract_epi32(sum, 0) + _mm256_extract_epi32(sum, 1) ; 
        return index ;
}




void init_vector(int* vector, int size, int value, int index){
        for (int i = 0 ; i < size ; i++){
                vector[i] = 0 ;
        }
	vector[index] = value ;
}

void init_vector(float* vector, int size, float value, int index){
        for (int i = 0 ; i < size ; i++){
                vector[i] = 0 ;
        }
        vector[index] = value ;
}


