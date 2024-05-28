#pragma once

#include "util.hpp"
#include <vector>

class Vertex{
  VertexID vertexID;
  VertexLabel vertexLabel;

  public:
    Vertex(VertexID id, VertexLabel label);
};

class Edge{
  friend class Graph;

private:
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
  friend class PathTable;
  friend class Path;
  friend class Edge;

public:
  std::vector<Vertex> vertexList;
  std::vector<Edge> edgeList;

public:
  Graph(const std::vector<std::vector<int>>& adjMatrix);

  Graph(const std::vector<std::vector<std::pair<int, int>>>& sparseAdjMatrix);

  std::vector<EdgeID> getEdges(VertexID endVertex, VertexID startVertex); // returns a list of all edges between two vertices.

  VertexID getStartVertex(EdgeID edgeID) const { return edgeList[edgeID].startVertexID; }
  VertexID getEndVertex(EdgeID edgeID) const { return edgeList[edgeID].endVertexID; }

};
