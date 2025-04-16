#pragma once

#include "Path.hpp"
#include "util.hpp"

class PathOrder {
public:
    
  PathOrder(const std::vector<WeightVector>& edgeWeights, const std::vector<int>& edgeOrder = {}) : 
    mEdgeOrder(edgeOrder)
  {
    mWeightLength = edgeWeights[0].size();
    mHasWeights = true;
    for (auto& wt : edgeWeights) {
     size_t currentIndex = mEdgeWeights.size();
     mEdgeWeights.push_back(WeightVector {});
     mEdgeWeights[currentIndex].resize(mWeightLength);
     std::copy(wt.begin(), wt.end(), mEdgeWeights[currentIndex].begin());
    }
  }

  PathOrder(const std::vector<int>& edgeOrder) :
    mEdgeWeights(),
    mEdgeOrder(edgeOrder),
    mWeightLength(0),
    mHasWeights(false) {};

  PathOrder() :
    mEdgeWeights(),
    mEdgeOrder({}),
    mWeightLength(0),
    mHasWeights(false) {};

  Compare comparePaths(const Path& path1, const Path& path2) const;
private:
  Compare weightCompare(const Path& path1, const Path& path2) const;
  Compare lengthLexCompare(const Path& path1, const Path& path2) const;
  WeightVector pathWeight(const Path& path) const;

  std::vector<WeightVector> mEdgeWeights;
  std::vector<int> mEdgeOrder;
  int mWeightLength;
  bool mHasWeights;
};
