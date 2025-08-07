#include "cpp_stl_find.hpp"

int cpp_find(int* vector, int size, int value) {
    int* pindex = std::find(vector, vector + size, value);
    // Theoretically, we have to verify vector[pindex] == value ...
    return pindex - vector;
}

int cppvector_find(std::vector<int>& vector, int value) {
    auto aindex = std::find(vector.begin(), vector.end(), value);
    // Theoretically, we have to verify vector[pindex] == value ...
    return std::distance(vector.begin(), aindex);
}
