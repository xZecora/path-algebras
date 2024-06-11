#pragma once
#include <string>
#include <vector>

/*
   Make aliases for some types for more clarity when reading and
   less confusion when coding
*/
using VertexID = int;
using EdgeID = int;
using PathID = int;
using VertexLabel = std::string;
using EdgeLabel = std::string;
using WeightVector = std::vector<int>;

enum class Compare { EQ, LT, GT };

template <typename T>
std::vector<T> concatVectors(std::vector<T> vec1, std::vector<T> vec2)
{
    std::vector<T> newVector = vec1;
    newVector.insert(newVector.end(), vec2.begin(), vec2.end());
    return newVector;
}
