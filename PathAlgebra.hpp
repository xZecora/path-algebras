#pragma once

#include "PathTable.hpp"
#include "Path.hpp"
#include "Graph.hpp"
#include "Field.hpp"

#include <vector>

class PathAlgebra
{
public:
  PathAlgebra(Graph& graph, Field& field) :
    mGraph(graph),
    mField(field)
  {
    mPathTable = PathTable();
  }

  PathID multiplyPaths(Path path1, Path path2);

  void addToPathTable(Path& path)
  {
    this->mPathTable.addToTable(path);
  }

private:
  Graph& mGraph;
  Field& mField;
  PathTable mPathTable;
};
