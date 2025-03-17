#include "util.hpp"
#include "PathAlgebra.hpp"
#include "SumCollector.hpp"
#include "PAElement.hpp"
#include <iostream>

long long TermCompare::totalTime = 0;

// this checks whether lhs < rhs
bool TermCompare::operator()(Term lhs, Term rhs)
{
  // assume that lhs and rhs != 1 error otherwise...
  //if(lhs.mPathID != -1 || rhs.mPathID != -1)
  //{
      
  //}
  auto pathDict = mPathAlgebra.mPathTable.pathDictionary();
  //auto startTime = std::chrono::high_resolution_clock::now();
  bool retVal = (mPathAlgebra.mPathOrder.comparePaths(pathDict[lhs.pathID],
					       pathDict[rhs.pathID]) == Compare::LT);
  //auto endTime = std::chrono::high_resolution_clock::now();
  //auto duration = duration_cast<std::chrono::nanoseconds>(endTime-startTime);
  //totalTime += duration.count();
  return retVal;
}

void SumCollector::add(const PAElement& f)
{
   std::for_each(f.cbegin(),f.cend(), [&](const Term& t) { mQueue.push(t); });
}

void SumCollector::add(const std::vector<PAElement>& fVec)
{
   std::for_each(fVec.cbegin(), fVec.cend(), [&](const PAElement& f) { add(f); } );
}

void SumCollector::subtract(const PAElement& f)
{
   std::for_each(f.cbegin(),f.cend(), [&](const Term& t) { 
     auto newTerm = t;
     newTerm.coeff = mPathAlgebra.mField.negate(t.coeff);
     mQueue.push(newTerm); }
   );
}

Term SumCollector::leadTerm()
{
  // this function pops elements off the top of the queue
  // until the pathid of the top changes.

  // if the queue is empty, return the "empty" term
  Term retVal;

  while (!mQueue.empty() && retVal.coeff.isZero())
  {
    auto queueTop = mQueue.top();
    retVal.pathID = queueTop.pathID;
    
    while (!mQueue.empty() && mQueue.top().pathID == queueTop.pathID)
    {
      retVal.coeff = mPathAlgebra.mField.add(retVal.coeff,mQueue.top().coeff);
      mQueue.pop();
    }
    // if all terms cancel, then reset pathID
    if (retVal.coeff.isZero()) retVal.pathID = 0;
  }
  return retVal;
}

PAElement SumCollector::value()
{
  PAElement retVal;
  if (mQueue.empty()) return retVal;
  
  Term curTerm;
  while (!mQueue.empty())
  {
    curTerm = leadTerm();
    if (!curTerm.coeff.isZero())
      retVal.polynomial.push_back(curTerm);
  }
  return retVal;
}
