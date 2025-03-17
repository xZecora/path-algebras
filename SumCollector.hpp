#pragma once

#include <queue>
#include <vector>
#include <chrono>
#include <iostream>

class PathAlgebra;
class PAElement;
class Term;

class TermCompare {
  private:
  
  const PathAlgebra& mPathAlgebra;

  public:
  TermCompare(const PathAlgebra& pathAlgebra) :
    mPathAlgebra(pathAlgebra) { }

  bool operator()(Term lhs, Term rhs);

  static long long totalTime;
};

class SumCollector {
public:
  SumCollector(const PathAlgebra& pathAlgebra) :
    mPathAlgebra(pathAlgebra),
    mTermCompare(pathAlgebra),
    mQueue(mTermCompare) {}

  // add or subtract a PAElement to the heap
  void add(const PAElement& f);
  void add(const std::vector<PAElement>& f);
  void subtract(const PAElement& f);
  
  void printTime(std::ostream& o) { o << "Total Time: " << mTermCompare.totalTime
                                      << std::endl << std::flush; }

  // pop all values from the heap, and return its sum
  PAElement value();

private:

  // remove all elements from the heap that have the
  // same PathID as the top
  Term leadTerm();

  const PathAlgebra &mPathAlgebra;
  TermCompare mTermCompare;
  std::priority_queue<Term,std::vector<Term>,TermCompare> mQueue;
};
