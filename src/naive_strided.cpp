#include <iostream>
#include <immintrin.h>

#include "find.hpp"


const int size = 1024*4 ; 

int main(){
        int* vector = (int*) malloc(sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1 - 3);
        int index = 0;
	int loop = 1 ; 
	for (int i = 0 ; i < loop ; i++){
	        index += naive_stride_find(vector, size, value);
	}

	std::cout << " Index position : " << (index/loop)/4 << std::endl ; 
}




