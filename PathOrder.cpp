#include <numeric>
#include "PathOrder.hpp"

WeightVector PathOrder::pathWeight(const Path& path1) const {
  WeightVector weightVector; // weight of the path
  // fill out weight vectors to be right size
  weightVector.resize(mWeightLength);
  std::fill(weightVector.begin(), weightVector.end(), 0);

  std::cout << "Weight Length: " << mWeightLength << std::endl;
  for (auto i : weightVector) { std::cout << i << " "; }

  std::cout << std::endl << std::flush;
  
  for (auto wt : mEdgeWeights) {
    for (auto i : wt) { std::cout << i << " "; }
  }

  // get and store edge list from our path
  const std::vector<EdgeID>& edgeList = path1.getEdgeList();
  int size = edgeList.size();

  // iterating over the edge list of the path
  for(int i = 0; i < size; i++){
    // TODO
    //assert(mEdgeWeights[i].size() == mWeightLength);
    for(int j = 0; j < mWeightLength; j++) {
      weightVector[j] += mEdgeWeights[i][j];
    }
  }
  return weightVector;
}

// TODO: have a version of pathWeight which accepts an integer i
//       and returns the ith component of the path weight
//       rather than the entire weight vector.  Then use that in weightCompare
//       and compute the weight vector on the fly for the comparison.

/* This function takes two paths and compares there total
   weights to see which is larger, then returns enum values
   for each possibility
*/
Compare PathOrder::weightCompare(const Path& path1, const Path& path2) const
{
  WeightVector weightVector1 = pathWeight(path1);
  WeightVector weightVector2 = pathWeight(path2);

  for(int i = 0; i < weightVector1.size(); i++)
  {
    if (weightVector1[i] > weightVector2[i])
      return Compare::GT;
    else if (weightVector1[i] < weightVector2[i])
      return Compare::LT;
  }
  return lengthLexCompare(path1, path2);
}

/*
 * This function takes in two paths and compares first the length
 * of each list, but if each list is equal length, then it compares
 * the order of the lists, and the one which has an earlier EdgeID is
 * considered smaller
 */
Compare PathOrder::lengthLexCompare(const Path& path1, const Path& path2) const
{
  if (path1.length() > path2.length()) return Compare::GT;
  if (path1.length() < path2.length()) return Compare::LT;
  std::vector<EdgeID> path1List = path1.getEdgeList();
  std::vector<EdgeID> path2List = path2.getEdgeList();

  for(int i = 0; i < path1.length(); i++)
  {
     if(path1List[i] < path2List[i])
       return Compare::LT;
     if(path1List[i] > path2List[i])
       return Compare::GT;
  }

  return Compare::EQ;
}

Compare PathOrder::comparePaths(const Path& path1, const Path& path2) const
{
   if (mHasWeights)
   {
      std::cout << "Has weights" << std::endl;
      return weightCompare(path1, path2);
   }
   return lengthLexCompare(path1,path2);
}
