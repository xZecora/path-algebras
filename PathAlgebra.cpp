#include "PathAlgebra.hpp"
#include "util.hpp"
//#include <algorithm>

PathID PathAlgebra::multiplyPaths(Path path1, Path path2)
{
  if (path1.mIsVertex)
  {
    if(path1.mEndVertex == path2.mStartVertex)
    {
      // This needs a lookup to check if it exists in the table at all
      return path2.mPathID;
    } else {
      return PathID(0); // ID of the empty path.
    }
  }

  if (path2.mIsVertex)
  {
    if(path1.mEndVertex == path2.mStartVertex)
    {
      // This needs a lookup to check if it exists in the table at all
      return path1.mPathID;
    } else {
      return PathID(0); // ID of the empty path.
    }
  }

  // TODO Write a check for if either path is just a vertex, return whichever is not if compatible.
  if (!(path1.mStartVertex == -1 || path2.mStartVertex == -1) && path1.mEndVertex == path2.mStartVertex){
    // perhaps have a constructor for concatenation?
    Path newPath = Path(path1.mStartVertex, path2.mEndVertex, concatVectors(path1.mPath, path2.mPath), false);

    // Need to know if our new path has been made already. If it hasn't, then we want to append it to he dictionary and set the ID,
    // otherwise, just set the ID
    auto lookup = mPathTable.mReversePathDictionary.find(newPath);

    if(lookup == mPathTable.mReversePathDictionary.end()) {
      newPath.mPathID = mPathTable.mPathDictionary.size();               // now give it its ID
      mPathTable.addToTable(newPath);                                    // add newPath to both of our path tables
      return newPath.mPathID;                                            // return it
    } else {
      return lookup->second; // it already exists, just return that.
    }

  } else {
    return PathID(0); // ID of the empty path.
  }
}

void PathAlgebra::add(PAElement &result, const PAElement &f, const PAElement &g) {
  size_t fsize = f.polynomial.size();
  size_t gsize = g.polynomial.size();

  // this should compare path weights at each step and add which is heavier
  auto fit = f.polynomial.begin();
  auto git = g.polynomial.begin();
  while (fit != f.polynomial.end() && git != g.polynomial.end()) {
    // if f heavier, add f
    if (mPathOrder.comparePaths(this->mPathTable.mPathDictionary[int(fit->second)], this->mPathTable.mPathDictionary[int(git->second)]) == Compare::GT){
      result.polynomial.push_back({fit->first,fit->second});
      ++fit;
    }
    // if g heavier, add g
    if (mPathOrder.comparePaths(this->mPathTable.mPathDictionary[int(fit->second)], this->mPathTable.mPathDictionary[int(git->second)]) == Compare::LT){
      result.polynomial.push_back({git->first,git->second});
      ++git;
    }
    // if f heavier, add f
    if (mPathOrder.comparePaths(this->mPathTable.mPathDictionary[int(fit->second)], this->mPathTable.mPathDictionary[int(git->second)]) == Compare::EQ){
      result.polynomial.push_back({mField.add(fit->first,git->first) ,fit->second});
      ++fit;
      ++git;
    }
  }

  // add everything from f not already used 
  while (fit != f.polynomial.end()) {
    result.polynomial.push_back({fit->first,fit->second});
    ++fit;
  }
  // add everything from g not already used 
  while (git != g.polynomial.end()) {
    result.polynomial.push_back({git->first,git->second});
    ++git;
  }
}

void PathAlgebra::subtract(PAElement &result, const PAElement &f, const PAElement &g) {

}

void PathAlgebra::negate(PAElement &result, const PAElement& f) {

}

void PathAlgebra::negate(PAElement &f) {

}

void PathAlgebra::multiply(PAElement &result, const PAElement &f, const PAElement &g) {

}

void PathAlgebra::exponent(PAElement &result, const PAElement &f, long n) {

}

