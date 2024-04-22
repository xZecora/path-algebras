#pragma once
#include "util.hpp"
#include "PathTable.hpp"
#include <vector>

class Vertex{
  VertexID vertexID;
  VertexLabel vertexLabel;

  public:
    Vertex(VertexID id, VertexLabel label);
};

class Edge{
  EdgeID edgeID;
  EdgeLabel edgeLabel;
  VertexID startVertexID;
  VertexID endVertexID;
  std::vector<int> edgeWeight; // Need to store this to reference elsewhere

  public: 
    Edge(EdgeID id, EdgeLabel label, VertexID startVertexID, VertexID endVertexID, std::vector<int> weight);
    Edge(EdgeID id, EdgeLabel label, VertexID startVertexID, VertexID endVertexID);

    std::vector<int> getWeight(); // need to access weight nonlocally
};

class Graph{
  friend PathTable;

  std::vector<Vertex> vertexList;
  std::vector<Edge> edgeList;

  std::vector<EdgeID> getEdges(VertexID endVertex, VertexID startVertex); // returns a list of all edges between two vertices.

  Graph(std::vector<std::vector<std::pair<int, int>>>);
};
