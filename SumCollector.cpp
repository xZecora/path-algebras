#include "util.hpp"
#include "PathAlgebra.hpp"
#include "SumCollector.hpp"
#include "PAElement.hpp"

// this checks whether lhs < rhs
bool TermCompare::operator()(Term lhs, Term rhs) const
{
  // assume that lhs and rhs != 1 error otherwise...
  //if(lhs.mPathID != -1 || rhs.mPathID != -1)
  //{
      
  //}
  auto pathDict = mPathAlgebra.mPathTable.pathDictionary();
  return (mPathAlgebra.mPathOrder.comparePaths(pathDict[lhs.pathID],
					       pathDict[rhs.pathID]) == Compare::LT);
}

void SumCollector::add(const PAElement& f)
{
   std::for_each(f.cbegin(),f.cend(), [&](const Term& t) { mQueue.push(t); });
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
    if (mQueue.empty()) return retVal;

    auto queueTop = mQueue.top();
    Term retVal;
    retVal.pathID = queueTop.pathID;

    while (mQueue.top().pathID == queueTop.pathID)
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
