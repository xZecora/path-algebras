#include "PathAlgebra.hpp"
#include "util.hpp"
//#include <algorithm>

#include <cassert>
#include <chrono>

// to remove asserts, use compiler flag -DNDEBUG

// does not currently work, if one of these so a vertex and the other is not in the path table, then we try to add
// to table but cannot modify the PathID held by the Path object as they are const
// once we decide on how to handle that it should be fine. (This will fix the bug with path printing we were having)
PathID PathAlgebra::multiplyPaths(const Path& path1, const Path& path2)
{
  if (path1.mIsVertex)
  {
    if(path1.mEndVertex == path2.mStartVertex)
    {
      return mPathTable.findOrAdd(path2);
    } else {
      return PathID(0); // ID of the empty path.
    }
  }

  if (path2.mIsVertex)
  {
    if(path1.mEndVertex == path2.mStartVertex)
    {
      return mPathTable.findOrAdd(path1);
    } else {
      return PathID(0); // ID of the empty path.
    }
  }

  // TODO Write a check for if either path is just a vertex, return whichever is not if compatible.
  if (!(path1.mStartVertex == -1 || path2.mStartVertex == -1) && path1.mEndVertex == path2.mStartVertex){
    // perhaps have a constructor for concatenation?
    Path newPath = Path(path1.mStartVertex, path2.mEndVertex, concatVectors(path1.mPath, path2.mPath), false);

    return mPathTable.findOrAdd(newPath);
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

  assert(result.polynomial.size() == 0);

  // this should compare path weights at each step and add which is heavier
  auto fit = f.polynomial.begin();
  auto git = g.polynomial.begin();

  while (fit != f.polynomial.end() && git != g.polynomial.end()) {
    const Path& fPath = this->mPathTable.mPathDictionary[int(fit->pathID)];
    const Path& gPath = this->mPathTable.mPathDictionary[int(git->pathID)];

    // if fPath heavier, add from f
    Compare comp = mPathOrder.comparePaths(fPath,gPath);

    switch (comp) {
      case Compare::GT:
	      result.polynomial.push_back({fit->coeff,fit->pathID});
	      ++fit;
	      break;
      case Compare::LT:
	      result.polynomial.push_back({git->coeff,git->pathID});
	      ++git;
	      break;
      case Compare::EQ:
              FieldElement sum = mField.add(fit->coeff,git->coeff);
              // if our sum is 0, then we dont want to add it and just want to move on.
              if(!sum.isZero())
	        result.polynomial.push_back({sum ,fit->pathID});
	      ++fit;
	      ++git;
	      break;
    }
  }

  // add everything from f not already used 
  while (fit != f.polynomial.end()) {
    result.polynomial.push_back({fit->coeff,fit->pathID});
    ++fit;
  }
  // add everything from g not already used 
  while (git != g.polynomial.end()) {
    result.polynomial.push_back({git->coeff,git->pathID});
    ++git;
  }
}


void PathAlgebra::add(PAElement &result, const std::vector<PAElement> &vec) {
  // could make this heap-based, but for now:
  assert(result.polynomial.size() == 0);

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

  assert(result.polynomial.size() == 0);
  // this should compare path weights at each step and add which is heavier
  auto fit = f.polynomial.begin();
  auto git = g.polynomial.begin();

  while (fit != f.polynomial.end() && git != g.polynomial.end()) {
    const Path& fPath = this->mPathTable.mPathDictionary[int(fit->pathID)];
    const Path& gPath = this->mPathTable.mPathDictionary[int(git->pathID)];

    // if fPath heavier, add from f
    Compare comp = mPathOrder.comparePaths(fPath,gPath);

    switch (comp) {
      case Compare::GT:
	      result.polynomial.push_back({fit->coeff,fit->pathID});
	      ++fit;
	      break;
      case Compare::LT:
	      result.polynomial.push_back({mField.negate(git->coeff),git->pathID});
	      ++git;
	      break;
      case Compare::EQ:
              FieldElement diff = mField.subtract(fit->coeff,git->coeff);
              // if our sum is 0, then we dont want to add it and just want to move on.
              if(!diff.isZero())
	        result.polynomial.push_back({diff ,fit->pathID});
	      ++fit;
	      ++git;
	      break;
    }
  }

  // add everything from f not already used 
  while (fit != f.polynomial.end()) {
	  result.polynomial.push_back({fit->coeff,fit->pathID});
    ++fit;
  }
  // add everything from g not already used 
  while (git != g.polynomial.end()) {
	  result.polynomial.push_back({mField.negate(git->coeff),git->pathID});
    ++git;
  }
}

void PathAlgebra::negate(PAElement &result, const PAElement &f) {
  assert(result.polynomial.size() == 0);
  for (auto t : f.polynomial)
    result.polynomial.push_back({mField.negate(t.coeff),t.pathID});
}

void PathAlgebra::negate(PAElement &f) {
  for (auto t : f.polynomial)
     t.coeff = mField.negate(t.coeff);
}

void PathAlgebra::multiply(PAElement &result, const PAElement &f, const PAElement &g)
{
  assert(result.polynomial.size() == 0);
  if (f.polynomial.size() < g.polynomial.size())
     multiplyShortLeft(result, f, g);
  else
     multiplyShortRight(result, f, g);
}

void PathAlgebra::multiplyShortLeft(PAElement &result, const PAElement &shortPoly, const PAElement &longPoly)
{
   assert(result.polynomial.size() == 0);
   std::vector<PAElement> tempVec;
   for (const auto &t : shortPoly.polynomial)
   {
      PAElement tempElt;
      leftMultiply(tempElt, t.pathID, t.coeff, longPoly);
      tempVec.push_back(tempElt);
   }
   auto startTime = std::chrono::high_resolution_clock::now();
   add(result,tempVec);
   auto endTime = std::chrono::high_resolution_clock::now();
   auto duration = duration_cast<std::chrono::microseconds>(endTime-startTime);
   std::cout << "Duration for vector sum: " << duration.count() << "ms" << std::endl << std::flush;
}

void PathAlgebra::multiplyShortRight(PAElement &result, const PAElement &longPoly, const PAElement &shortPoly)
{
   assert(result.polynomial.size() == 0);
   std::vector<PAElement> tempVec;
   for (const auto &t : shortPoly.polynomial)
   {
      PAElement tempElt;
      rightMultiply(tempElt, longPoly, t.pathID, t.coeff);
      tempVec.push_back(tempElt);
   }
   auto startTime = std::chrono::high_resolution_clock::now();
   add(result,tempVec);
   auto endTime = std::chrono::high_resolution_clock::now();
   auto duration = duration_cast<std::chrono::microseconds>(endTime-startTime);
   std::cout << "Duration for vector sum: " << duration.count() << "ms" << std::endl << std::flush;
}

void PathAlgebra::leftMultiply(PAElement &result, const Path &p, const FieldElement &c, const PAElement &f)
{
  assert(result.polynomial.size() == 0);
  // this function multiplies f by cp on the left.
  // this function assumes result is empty before this call.
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(p,t.pathID);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.coeff);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::leftMultiply(PAElement &result, const Path &p, const PAElement &f)
{
   assert(result.polynomial.size() == 0);
   leftMultiply(result, p, FieldElement {1}, f);
}

void PathAlgebra::leftMultiply(PAElement &result, const PathID &p, const FieldElement &c, const PAElement &f)
{
   assert(result.polynomial.size() == 0);
   // this function assumes that p is a valid PathID
   // assert(p.getID() != -1);
   for (const auto &t : f.polynomial)
   {
     PathID tempPathID = multiplyPaths(p,t.pathID);
     if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
     FieldElement tempCoeff = mField.multiply(c,t.coeff);
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
    PathID tempPathID = multiplyPaths(t.pathID,p);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.coeff);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement& f, const Path &p)
{
  rightMultiply(result, f, p, FieldElement {1});
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement &f, const PathID &p, const FieldElement &c)
{
  assert(result.polynomial.size() == 0);
  // this function multiplies f by cp on the left.
  // this function assumes result is empty before this call.
  for (const auto &t : f.polynomial)
  {
    PathID tempPathID = multiplyPaths(t.pathID,p);
    if (tempPathID == 0) continue;  // this is the case when paths multiply to zero
    FieldElement tempCoeff = mField.multiply(c,t.coeff);
    result.polynomial.push_back({tempCoeff, tempPathID});
  } 
}

void PathAlgebra::rightMultiply(PAElement &result, const PAElement&f, const PathID &p)
{
  rightMultiply(result, f, p, FieldElement {1});
}

void PathAlgebra::exponent(PAElement &result, const PAElement &f, long n) {
   // exponents must be nonnegative
   assert(n >= 0);
   switch (n) {
     case 0:
        //result = paOne;
        break;
     case 1:
	result = f;
	break;
     default:
        result = f;
        for (auto i = 1; i < n; ++i)
	{
	   PAElement tmp;
	   multiply(tmp, result, f);
	   result = tmp;
	}
   }
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
     std::string out;
     out = mGraph.printPathByLabel(mPathTable.mPathDictionary[t.pathID]);
     ostr << t.coeff << "*" << out;
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
     const Path& thisPath = mPathTable.mPathDictionary[t.pathID];
     std::string out = mGraph.printEdgeID(thisPath);
     std::string leftDelim,rightDelim;
     if (not thisPath.mIsVertex)
     {
        leftDelim = "[";
	rightDelim = "]";
     }
     else
     {
        leftDelim = "{";
	rightDelim = "}";
     }
     ostr << t.coeff << "*" << leftDelim << out << rightDelim;
     if (thisTerm != numTerms) ostr << " + ";
     ++thisTerm;
   }
}

// input divisors should be preprocessed such that each path inside them starts and ends at the same position as all the others.
void PathAlgebra::dividePAElement(const std::vector<PAElement> divisors, const PAElement dividend){
  PAElement curDividend = dividend;
  while(curDividend.polynomial != {}){
    dividend.polynomial[0].pathID;
  }
}

std::pair<int,int> PathAlgebra::isAnySubword(const std::vector<PathID>& subIDDict, const PathID& superPathID){
  std::vector<EdgeID> word = PathTable.mPathDictionary[superPathID].getEdgeList();
  size_t wordLen = PathTable.mPathDictionary[superPathID].length();
  int j = 0;
  for (int i = 0; i < wordLen; i++)
  {
    for (int j = 0; j < subDict.size(); ++j)
    {
      if(!(wordLen-i <= PathTable.mPathDictoinary[subDict[j]].length()) &&
         word[i] == PathTable.mPathDictoinary[subDict[j]].mPath[0] &&
         memcmp(&(word[i]),
                &PathTable.mPathDictoinary[subDict[j]].mPath[0],
                PathTable.mPathDictoinary[subDict[j]].length() * sizeof(EdgeID)))
        return {i,j};
      ++j;
    }
  }
  return {-1,-1};
}

int PathAlgebra::isSubword(const PathID& subPathID, const PathID& superPathID) {
  std::vector<EdgeID> subword = PathTable.mPathDictionary[subPathID].getEdgeList();
  std::vector<EdgeID> word = PathTable.mPathDictionary[superPathID].getEdgeList();
  size_t wordLen = word.size();
  size_t subLen = subword.size();
  

  for (int i = 0; i < wordLen; i++)
  {
    if(wordLen-i <= subLen)
      break;
    if(word[i] == subword[0] && memcmp(&(word[i]), &subword[0], subLen))
      return i;
  }

  return -1;
}

int PathAlgebra::findOverlap(const PathID& prefix, const PathID& suffix){
  for (int i = 0; i < this->length(); i++){
    if((this->length()-i) <= PathTable.mPathDictionary[prefix].length() &&
       memcmp(&(PathTable.mPathDictionary[suffix].mPath[i]),
              &(PathTable.mPathDictionary[prefix].mPath[0]),
              (PathTable.mPathDictionary[suffix].length() - i) * sizeof(EdgeID)))
      return i;
  }
  return -1;
}
