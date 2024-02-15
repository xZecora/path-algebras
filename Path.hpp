#include "Graph.hpp"
#include <unordered_map>

class Path{
  bool isZero;
  bool isVertex;
  VertexID startVertex;
  VertexID endVertex;
  PathID pathID;
  std::vector<EdgeID> thePath;
};

class PathTable{
  std::vector<Path> pathDictionary;
  std::unordered_map<Path,PathID> reversePathDictionary;
};

class PathAlgebra{
  Graph graph;
  PathTable myPathTable;
  Path multiplyPaths(Path path1, Path path2);
  PathAlgebra(std::vector<std::vector<int>> matrix, std::vector<std::string>, std::vector<std::string>);

};
