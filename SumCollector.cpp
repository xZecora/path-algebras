#include "util.hpp"
#include "PathAlgebra.hpp"
// #include "SumCollector.hpp"

// this checks whether lhs < rhs
bool PathIDCompare::operator()(PathID lhs, PathID rhs) const
{
  // assume that lhs and rhs != 1 error otherwise...
  //if(lhs.mPathID != -1 || rhs.mPathID != -1)
  //{
      
  //}
  auto pathDict = mPathAlgebra.mPathTable.pathDictionary();
  return (mPathAlgebra.mPathOrder.comparePaths(pathDict[lhs],pathDict[rhs]) == Compare::LT);
}

