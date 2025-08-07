#ifndef INTRINSIC_FIND_HPP
#define INTRINSIC_FIND_HPP

#include <immintrin.h>

int intrinsic_find(int* vector, int size, int value);
int intrinsic_find(float* vector, int size, float value);
int intrinsic2_find(int* vector, int size, int value);

#endif // INTRINSIC_FIND_HPP
