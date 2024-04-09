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
int PathOrder::comparePaths(Path path1, Path path2){
  WeightVector weightVector1 = pathWeight(path1);
  WeightVector weightVector2 = pathWeight(path2);

  int size1 = weightVector1.size();
  int size2 = weightVector2.size();

  int total1 = 0;
  int total2 = 0;

  for(int i = 0; i < size1; i++)
    total1 += weightVector1[i];

  for(int i = 0; i < size2; i++)
    total2 += weightVector2[i];

  if(total1 > total2)
    return GT;

  if(total1 < total2)
    return LT;

  return EQ;
}
