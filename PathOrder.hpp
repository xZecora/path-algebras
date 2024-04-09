#pragma once

#include "Path.hpp"
#include "util.hpp"

enum class PathComp { EQ, LT, GT };

class PathOrder {
public:
    PathComp comparePaths(Path path1, Path path2);
private:
    std::vector<WeightVector> edgeWeights;
    WeightVector pathWeight(Path path);
};
