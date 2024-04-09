#include <numeric>
#include "PathOrder.hpp"

WeightVector PathOrder::pathWeight(Path path1){
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
   weights to see which is larger, then returnr enum values
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
}

Compare PathOrder::lengthLexCompare(const Path& path1, const Path& path2) const
{
  if (path1.length() > path2.length()) return Compare::GT;
  if (path1.length() < path2.length()) return Compare::LT;

  for(int i = 0; i < path1.length(); i++)
  {
     // TODO
  }

  return EQ;
}

Compare PathOrder::comparePaths(const Path& path1, const Path& path2) const
{
   Compare result;
   if (hasWeights)
   {
      result = weightCompare(path1, path2);
      if (result != Compare::EQ) return result;
   }
   return lengthLexCompare(path1,path2);
}
