#include <iostream>
#include <immintrin.h>

#include "find.hpp"


const int size = 1024 ; 

int main(){
        float* vector = (float*) malloc(sizeof(float) * size) ;
        float value = 1.0f ;
        init_vector(vector, size, value, size-1);
        int index = 0;
        int loop = 1 ;
        for (int i = 0 ; i < loop ; i++){
                index += intrinsic_find(vector, size, value);
        }

        std::cout << " Index position : " << index/loop << std::endl ;


}




