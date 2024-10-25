#include "PathAlgebra.hpp"
#include "util.hpp"
//#include <algorithm>

PathID PathAlgebra::multiplyPaths(const Path& path1, const Path& path2)
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

PathID PathAlgebra::multiplyPaths(PathID path1, PathID path2)
{
  return multiplyPaths(mPathTable.mPathDictionary[path1],mPathTable.mPathDictionary[path2]);
}

PathID PathAlgebra::multiplyPaths(const Path& path1, PathID path2)
{
  return multiplyPaths(path1,mPathTable.mPathDictionary[path2]);
}

PathID PathAlgebra::multiplyPaths(PathID path1, const Path& path2)
{
  return multiplyPaths(mPathTable.mPathDictionary[path1],path2);
}

void PathAlgebra::add(PAElement &result, const PAElement &f, const PAElement &g) {

  // this should compare path weights at each step and add which is heavier
  auto fit = f.polynomial.begin();
  auto git = g.polynomial.begin();

  while (fit != f.polynomial.end() && git != g.polynomial.end()) {
    std::cout << "Getting paths." << std::endl;
    const Path& fPath = this->mPathTable.mPathDictionary[int(fit->second)];
    const Path& gPath = this->mPathTable.mPathDictionary[int(git->second)];

    std::cout << mGraph.printEdgeLabel(fPath) << std::endl;
    std::cout << mGraph.printEdgeLabel(gPath) << std::endl;

    std::cout << "About to compare paths." << std::endl;
    // if fPath heavier, add from f
    Compare comp = mPathOrder.comparePaths(fPath,gPath);

    switch (comp) {
      case Compare::GT:
	      std::cout << "f heavier" << std::endl;
	      result.polynomial.push_back({fit->first,fit->second});
	      ++fit;
	      break;
      case Compare::LT:
	      std::cout << "g heavier" << std::endl;
	      result.polynomial.push_back({git->first,git->second});
	      ++git;
	      break;
      case Compare::EQ:
	      std::cout << "f and g same" << std::endl;
              FieldElement sum = mField.add(fit->first,git->first);
              // if our sum is 0, then we dont want to add it and just want to move on.
              if(!sum.isZero())
	        result.polynomial.push_back({sum ,fit->second});
	      ++fit;
	      ++git;
	      break;
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


void PathAlgebra::add(PAElement &result, const std::vector<PAElement> &vec) {
  // could make this heap-based, but for now:
  PAElement accum;
  for (auto f : vec)
  {
    PAElement temp;
    add(temp,f,accum);
    accum = temp;  // TODO: fast way of moving memory from one to another
  }
  result = accum;  // TODO: also use memory move
}


void PathAlgebra::subtract(PAElement &result, const PAElement &f, const PAElement &g) {

  // this should compare path weights at each step and add which is heavier
  auto fit = f.polynomial.begin();
  auto git = g.polynomial.begin();

  while (fit != f.polynomial.end() && git != g.polynomial.end()) {
    std::cout << "Getting paths." << std::endl;
    const Path& fPath = this->mPathTable.mPathDictionary[int(fit->second)];
    const Path& gPath = this->mPathTable.mPathDictionary[int(git->second)];

    std::cout << mGraph.printEdgeLabel(fPath) << std::endl;
    std::cout << mGraph.printEdgeLabel(gPath) << std::endl;

    std::cout << "About to compare paths." << std::endl;
    // if fPath heavier, add from f
    Compare comp = mPathOrder.comparePaths(fPath,gPath);

    switch (comp) {
      case Compare::GT:
	      std::cout << "f heavier" << std::endl;
	      result.polynomial.push_back({fit->first,fit->second});
	      ++fit;
	      break;
      case Compare::LT:
	      std::cout << "g heavier" << std::endl;
	      result.polynomial.push_back({mField.negate(git->first),git->second});
	      ++git;
	      break;
      case Compare::EQ:
	      std::cout << "f and g same" << std::endl;
              FieldElement diff = mField.subtract(fit->first,git->first);
              // if our sum is 0, then we dont want to add it and just want to move on.
              if(!diff.isZero())
	        result.polynomial.push_back({diff ,fit->second});
	      ++fit;
	      ++git;
	      break;
    }
  }

  // add everything from f not already used 
  while (fit != f.polynomial.end()) {
	  result.polynomial.push_back({fit->first,fit->second});
    ++fit;
  }
  // add everything from g not already used 
  while (git != g.polynomial.end()) {
	  result.polynomial.push_back({mField.negate(git->first),git->second});
    ++git;
  }
}

void PathAlgebra::negate(PAElement &result, const PAElement &f) {
  for (auto t : f.polynomial)
    result.polynomial.push_back({mField.negate(t.first),t.second});
}

void PathAlgebra::negate(PAElement &f) {
  for (auto t : f.polynomial)
     t.first = mField.negate(t.first);
}

void PathAlgebra::multiply(PAElement &result, const PAElement &f, const PAElement &g) {

  PAElement result;
  std::vector<PAElement> tempVec;

  // TODO: fill tempVec with left/right multiples of f/g depending on which one is shorter

  add(result, tempVec);
}

void PathAlgebra::leftMultiply(PAElement &result, const Path &p, const FieldElement &c, const PAElement &f)
{
  // this function multiplies f by cp on the left.
  // this function assumes result is empty before this call.
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(p,t.second);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.first);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::leftMultiply(PAElement &result, const Path &p, const PAElement &f)
{
  leftMultiply(result, p, FieldElement {1}, f);
}

void PathAlgebra::leftMultiply(PAElement &result, const PathID &p, const FieldElement &c, const PAElement &f)
{
  // this function assumes that p is a valid PathID
  // assert(p.getID() != -1);
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(p,t.second);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.first);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}  
  
void PathAlgebra::leftMultiply(PAElement &result, const PathID &p, const PAElement &f)
{
  leftMultiply(result, p, FieldElement {1}, f);
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement &f, const Path &p, const FieldElement &c)
{
  // this function multiplies f by cp on the left.
  // this function assumes result is empty before this call.
  // this version allows for p to be a path with -1 PathID
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(t.second,p);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.first);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement& f, const Path &p)
{
  rightMultiply(result, f, p, FieldElement {1});
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement &f, const PathID &p, const FieldElement &c)
{
  // this function multiplies f by cp on the left.
  // this function assumes result is empty before this call.
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(t.second,p);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.first);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement&f, const PathID &p)
{
  rightMultiply(result, f, p, FieldElement {1});
}

void PathAlgebra::exponent(PAElement &result, const PAElement &f, long n) {

}

void PathAlgebra::printPAElementByLabel(std::ostream& ostr, const PAElement &f)
{
   size_t numTerms = f.polynomial.size();
   if (numTerms == 0)
   {
      ostr << "0";
      return;
   }
   size_t thisTerm = 1;
   for (auto t : f.polynomial)
   {
     std::string out = mGraph.printEdgeLabel(mPathTable.mPathDictionary[t.second]);
     ostr << t.first << "*" << out;
     if (thisTerm != numTerms) ostr << " + ";
     ++thisTerm;
   }
}

void PathAlgebra::printPAElementByPathID(std::ostream& ostr, const PAElement &f)
{
   size_t numTerms = f.polynomial.size();
   if (numTerms == 0)
   {
      ostr << "0";
      return;
   }
   size_t thisTerm = 1;
   for (auto t : f.polynomial)
   {
     std::string out = mGraph.printEdgeID(mPathTable.mPathDictionary[t.second]);
     ostr << t.first << "*" << "[" << out << "]";
     if (thisTerm != numTerms) ostr << " + ";
     ++thisTerm;
   }
}
