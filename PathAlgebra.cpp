#include "PathAlgebra.hpp"
#include "util.hpp"
//#include <algorithm>

PathID PathAlgebra::multiplyPaths(Path path1, Path path2)
{
  // TODO Write a check for if either path is just a vertex, return whichever is not if compatible.
  // I think a placeholder variable is easiest here
  //Path newPath = Path();
  if (!(path1.mStartVertex == -1 || path2.mStartVertex == -1) && path1.mEndVertex == path2.mStartVertex){
    // perhaps have a constructor for concatenation?
    Path newPath = Path(path1.mStartVertex, path2.mEndVertex, concatVectors(path1.mPath, path2.mPath), false);
    // Need to know if our new path has been made already. If it hasn't, then we want to append it to he dictionary and set the ID,
    // otherwise, just set the ID
    auto lookup = mPathTable.mReversePathDictionary.find(newPath);
    if(lookup == mPathTable.mReversePathDictionary.end()) {
      newPath.mPathID = mPathTable.mPathDictionary.size();               // now give it its ID
      mPathTable.addToTable(newPath);                                    // add newPath to both of our path tables
      //mPathTable.mPathDictionary.push_back(newPath);                     // newPath is new, add it to our dictionary
      //mPathTable.mReversePathDictionary.insert({newPath,newPath.mPathID});   // also add it to the reverse dictionary
      return newPath.mPathID;                                            // return it
    } else {
      return lookup->second; // it already exists, just return that.
    }
  } else {
    return 0; // ID of the empty path.
  }
}
