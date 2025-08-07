#include "utils.hpp"

void init_vector(int* vector, int size, int value, int index) {
    for (int i = 0; i < size; i++) {
        vector[i] = 0;
    }
    vector[index] = value;
}

void init_vector(float* vector, int size, float value, int index) {
    for (int i = 0; i < size; i++) {
        vector[i] = 0;
    }
    vector[index] = value;
}
