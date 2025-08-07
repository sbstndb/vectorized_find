#include "naive_find.hpp"

int naive_find(int* vector, int size, int value) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (vector[i] == value) {
            index = i;
            return index;
        }
    }
    return index;
}

int naive_stride_find(int* vector, int size, int value) {
    int index = -1;
    for (int i = 0; i < size; i += 4) {
        if (vector[i] == value) {
            index = i;
            return index;
        }
    }
    return index;
}

int nobreak_find(int* vector, int size, int value) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (vector[i] == value) {
            index = i;
            // Note: works if we do not have twice the value.
            // If the array is sorted, you can travel the vector
            // 	backwards and then get the first value
        }
    }
    return index;
}
