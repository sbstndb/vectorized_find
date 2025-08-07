#ifndef CPP_STL_FIND_HPP
#define CPP_STL_FIND_HPP

#include <algorithm> // For std::find
#include <vector>    // For std::vector
#include <iterator>  // For std::distance

int cpp_find(int* vector, int size, int value);
int cppvector_find(std::vector<int>& vector, int value);

#endif // CPP_STL_FIND_HPP
