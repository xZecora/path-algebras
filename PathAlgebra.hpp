#pragma once

#include "PathTable.hpp"
#include "Path.hpp"
#include "Graph.hpp"

#include <vector>

class PathAlgebra
{
public:
  PathAlgebra(std::vector<std::vector<int>> matrix, std::vector<std::string>, std::vector<std::string>);

  Path multiplyPaths(Path path1, Path path2);

private:
  Graph mGraph;
  PathTable mPathTable;
};
