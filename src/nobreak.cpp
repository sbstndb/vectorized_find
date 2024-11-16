#include <iostream>
#include <immintrin.h>

#include "find.hpp"


const int size = 1024 ; 

int main(){
        int* vector = (int*) malloc(sizeof(int) * size) ;
        int value = 1 ;
        init_vector(vector, size, value, size-1);
        int index ;
        index = nobreak_find(vector, size, value);

	std::cout << " Index position : " << index << std::endl ; 
}




