#pragma once

#include "Path.hpp"
#include "util.hpp"

class PathOrder {
public:
    Compare comparePaths(const Path& path1, const Path& path2) const;
private:
    Compare weightCompare(const Path& path1, const Path& path2) const;
    Compare lengthLexCompare(const Path& path1, const Path& path2) const;

    std::vector<WeightVector> edgeWeights;
    WeightVector pathWeight(Path path) const;
    bool hasWeights;
};
