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

class PathAlgebra
{
public:
  
  friend class SumCollector;
  friend class PathIDCompare;

  PathAlgebra(Graph& graph, Field& field) :
    mGraph(graph),
    mField(field),
    mPathTable(),
    mPathOrder(),
    mSumCollector(*this) {};

  PathAlgebra(Graph& graph, Field& field, PathOrder& pathOrder) :
    mGraph(graph),
    mField(field),
    mPathTable(),
    mPathOrder(pathOrder),
    mSumCollector(*this) {};

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
  int findOverlap(const PathID& prefix, const PathID& suffix);

  void addToPathTable(Path& path)
  {
    this->mPathTable.addToTable(path);
  }

  void add(PAElement &result, const PAElement &f, const PAElement &g);
  void subtract(PAElement &result, const PAElement &f, const PAElement &g);
  void negate(PAElement &result, const PAElement& f);
  void negate(PAElement &f);
  void multiply(PAElement &result, const PAElement &f, const PAElement &g);
  void exponent(PAElement &result, const PAElement &f, long n);

  void printPAElementByLabel(std::ostream& ostr, const PAElement &f);
  void printPAElementByPathID(std::ostream& ostr, const PAElement &f);

  void printPathTable() const;

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

  Graph& mGraph;
  Field& mField;
  PathTable mPathTable;
  PathOrder mPathOrder;
  SumCollector mSumCollector;
};
