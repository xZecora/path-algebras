#pragma once

#include "PathTable.hpp"
#include "Path.hpp"
#include "PathOrder.hpp"
#include "Graph.hpp"
#include "Field.hpp"
#include "PAElement.hpp"

#include <vector>

class PathAlgebra
{
public:
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

  PathID multiplyPaths(Path path1, Path path2);

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

private:
  Graph& mGraph;
  Field& mField;
  PathTable mPathTable;
  PathOrder mPathOrder;
};
