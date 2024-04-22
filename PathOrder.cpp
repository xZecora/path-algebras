#include <numeric>
#include "PathOrder.hpp"

WeightVector PathOrder::pathWeight(Path path1) const {
  WeightVector weightVector = {};
  int size = path1.getEdgeList().size();
  /*
     This does not work, this simply gets the id for each edge
     and adds it to the list. Need to implement accessing PathTables
     dictionary.
  */
  for(int i = 0; i < size; i++){
    weightVector.push_back(path1.getEdgeList()[size - i]);
  }
  return weightVector;
}

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
  return PathOrder::lengthLexCompare(path1, path2);
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
   Compare result;
   if (hasWeights)
   {
      return weightCompare(path1, path2);
   }
   return lengthLexCompare(path1,path2);
}
