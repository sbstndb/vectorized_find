#include "compare_find.hpp"

int compare_find(int* vector, int size, int value) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        index += (vector[i] < value);
    }
    return index;
}

int compare_find(float* vector, int size, float value) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        index += (vector[i] < value);
    }
    return index;
}
