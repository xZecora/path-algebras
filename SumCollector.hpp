#pragma once

#include <map>

class PathAlgebra;

class PathIDCompare {
  private:
  const PathAlgebra& mPathAlgebra;

  public:
  PathIDCompare(const PathAlgebra& pathAlgebra) :
    mPathAlgebra(pathAlgebra) { }

  bool operator()(PathID lhs, PathID rhs) const;
};


class SumCollector {
public:
  SumCollector(const PathAlgebra& pathAlgebra) :
    mPathAlgebra(pathAlgebra),
    mPathIDCompare(pathAlgebra),
    mMap(mPathIDCompare) {}

private:
  const PathAlgebra &mPathAlgebra;
  PathIDCompare mPathIDCompare;
  std::map<PathID,FieldElement,PathIDCompare> mMap;
};
