#pragma once

#include "PathTable.hpp"
#include "Path.hpp"
#include "PathOrder.hpp"
#include "Graph.hpp"
#include "Field.hpp"
#include "PAElement.hpp"
#include "SumCollector.hpp"

#include <vector>
#include <iostream>

struct OverlapInfo {
  int leftIndex, rightIndex;
  int overlapLocation;
  size_t lcmSize;
  size_t overlapSize;
  //std::vector<EdgeID> prefix, suffix;
};

class OverlapCompare {
  public:
  // Sorted by size, left term, right term, and overlapLocation, in that order.
  // If all these things are equal, it is the same overlap.
  bool operator()(OverlapInfo lhs, OverlapInfo rhs) {
    if(lhs.lcmSize == rhs.lcmSize)
      if(lhs.leftIndex == rhs.leftIndex)
        if(lhs.rightIndex == rhs.rightIndex)
          return lhs.overlapLocation >= rhs.overlapLocation;
        else
          return lhs.rightIndex >= rhs.rightIndex;
      else
        return lhs.leftIndex >= rhs.leftIndex;
    else
      return lhs.lcmSize >= rhs.lcmSize;
  }
};

class PathAlgebra
{
public:
  
  friend class SumCollector;
  friend class TermCompare;

  PathAlgebra(Graph& graph, Field& field) :
    mGraph(graph),
    mField(field),
    mPathTable(),
    mPathOrder() {};

  PathAlgebra(Graph& graph, Field& field, PathOrder& pathOrder) :
    mGraph(graph),
    mField(field),
    mPathTable(),
    mPathOrder(pathOrder) {};

  PathID multiplyPaths(const Path& path1, const Path& path2);
  PathID multiplyPaths(const Path& path1, PathID path2);
  PathID multiplyPaths(PathID path1, const Path& path2);
  PathID multiplyPaths(PathID path1, PathID path2);

  PAElement dividePAElement(const std::vector<PAElement> divisors, const PAElement dividend);

  PathID divisionAlgorithm_twoSidedMultiplyPaths(const std::vector<EdgeID>& leftPath, const Path& mainPath, const std::vector<EdgeID>& rightPath, VertexID startVertex, VertexID endVertex);
  PAElement divisionAlgorithm_twoSidedMultiply(const std::vector<EdgeID>& p, const FieldElement& coeff, const PAElement& f, const std::vector<EdgeID>& s, const VertexID& startVertex, const VertexID& endVertex);
  PAElement divisionAlgorithm_subtract(const PAElement& f, const PAElement& g);

  int isSubword(const PathID& subPathID, const PathID& superPathID);
  // return (i,j) where subword j in subDict is found in position i of word.
  std::pair<int,int> isAnySubword(const std::vector<PathID>& subIDDict, const PathID& superPathID);
  std::vector<int> findOverlaps(const PathID& prefix, const PathID& suffix) const;

  void addToPathTable(Path& path)
  {
    this->mPathTable.addToTable(path);
  }

  PAElement one();

  void add(PAElement &result, const PAElement &f, const PAElement &g);
  void subtract(PAElement &result, const PAElement &f, const PAElement &g);
  void negate(PAElement &result, const PAElement& f);
  void negate(PAElement &f);
  void multiply(PAElement &result, const PAElement &f, const PAElement &g);
  void multiplySC(PAElement &result, const PAElement &f, const PAElement &g);
  void exponent(PAElement &result, const PAElement &f, long n);
  void powers_of_2_exponent(PAElement &result, const PAElement &f, long n);
  void exponentSC(PAElement &result, const PAElement &f, long n);

  void makeMonic(PAElement& result) const;

  void printPAElementByLabel(std::ostream& ostr, const PAElement &f);
  void printPAElementByPathID(std::ostream& ostr, const PAElement &f);

  void printPathTable() const;

  std::vector<PAElement> Buchbergers(const std::vector<PAElement> &generators, int maximiumDegree, int maximumSize = 0);
  std::pair<PAElement,PAElement> Buchbergers_prefix_suffix(const PAElement &first, const PAElement &second);
  std::vector<OverlapInfo> Buchbergers_processOverlaps(const std::vector<PAElement> &list, const int &leftIndex, const int &rightIndex);

  PAElement divideOverlap(std::vector<PAElement> divisors, OverlapInfo dividend);

  PAElement Buchbergers_leftMultiply(const std::vector<EdgeID> &p, const FieldElement &c, const PAElement &f);

private:
  void add(PAElement &result, const std::vector<PAElement>& vec);

  void leftMultiply(PAElement &result, const Path &p, const FieldElement &c, const PAElement &f);
  void leftMultiply(PAElement &result, const Path &p, const PAElement &f);
  void rightMultiply(PAElement &result, const PAElement &f, const Path &p, const FieldElement &c);
  void rightMultiply(PAElement &result, const PAElement &f, const Path &p);
  void leftMultiply(PAElement &result, const PathID &p, const FieldElement &c, const PAElement &f);
  void leftMultiply(PAElement &result, const PathID &p, const PAElement &f);
  void rightMultiply(PAElement &result, const PAElement &f, const PathID &p, const FieldElement &c);
  void rightMultiply(PAElement &result, const PAElement &f, const PathID &p);
  
  void multiplyShortLeft(PAElement &result, const PAElement &shortPoly, const PAElement &longPoly);
  void multiplyShortRight(PAElement &result, const PAElement &longPoly, const PAElement &shortPoly);
  void multiplyShortLeftSC(PAElement &result, const PAElement &shortPoly, const PAElement &longPoly);
  void multiplyShortRightSC(PAElement &result, const PAElement &longPoly, const PAElement &shortPoly);

  Graph& mGraph;
  Field& mField;
  PathTable mPathTable;
  PathOrder mPathOrder;
};
