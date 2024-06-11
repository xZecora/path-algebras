#include "PathAlgebra.hpp"
#include "util.hpp"
//#include <algorithm>

PathID PathAlgebra::multiplyPaths(Path path1, Path path2)
{
  // I think a placeholder variable is easiest here
  //Path newPath = Path();
  if (!(path1.mStartVertex == -1 || path2.mStartVertex == -1) && path1.mEndVertex == path2.mStartVertex){
    //newPath.mStartVertex = path1.mStartVertex;    // set values in placeholder if the path is actually valid
    //newPath.mEndVertex = path2.mEndVertex;
    //newPath.mIsZero = false;
    //newPath.mIsVertex = false;
    //newPath.mPath = concatVectors(path1.mPath, path2.mPath);
    Path newPath = Path(path1.mStartVertex, path2.mEndVertex, concatVectors(path1.mPath, path2.mPath), false);
    // Need to know if our new path has been made already. If it hasn't, then we want to append it to he dictionary and set the ID,
    // otherwise, just set the ID
    //auto contains = std::find(mPathTable.mPathDictionary.begin(), mPathTable.mPathDictionary.end(), newPath);
    bool inside = mPathTable.mReversePathDictionary.contains(newPath);
    //if(contains == mPathTable.mReversePathDictionary.end()) {
    if(!inside) {
      std::cout << "New path: " << newPath.printID() << std::endl;
      PathHash hash;
      std::cout << "New path hash: " << hash(newPath) << std::endl;
      mPathTable.mPathDictionary.push_back(newPath);              // newPath is new, add it to our dictionary
      newPath.mPathID = mPathTable.mPathDictionary.size() - 1;    // now give it its ID
      return newPath.mPathID;                                             // return it
    } else {
      //return inside->second; // it already exists, just return that.
      return 0;
    }
  } else {
    return 0; // ID of the empty path.
  }
}
