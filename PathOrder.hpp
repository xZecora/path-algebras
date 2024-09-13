#pragma once

#include "Path.hpp"
#include "util.hpp"

class PathOrder {
public:
    
    PathOrder(std::vector<WeightVector>& edgeWeights) :
      mEdgeWeights(edgeWeights),
      mWeightLength(edgeWeights[0].size()),
      mHasWeights(true) {};

    PathOrder() :
      mEdgeWeights(),
      mWeightLength(0),
      mHasWeights(false) {};

    Compare comparePaths(const Path& path1, const Path& path2) const;
private:
    Compare weightCompare(const Path& path1, const Path& path2) const;
    Compare lengthLexCompare(const Path& path1, const Path& path2) const;
    WeightVector pathWeight(Path path) const;

    std::vector<WeightVector> mEdgeWeights;
    int mWeightLength;
    bool mHasWeights;
};
