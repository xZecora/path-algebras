#pragma once
#include "util.hpp"
#include <vector>

class Vertex{
  VertexID vertexID;
  VertexLabel vertexLabel;

  Vertex(VertexID id, VertexLabel label);
};

class Edge{
  EdgeID edgeID;
  EdgeLabel edgeLabel;
  VertexID startVertexID;
  VertexID endVertexID;

  Edge(EdgeID id, EdgeLabel label, VertexID startVertexID, VertexID endVertexID);
};

class Graph{
  std::vector<Vertex> vertexList;
  std::vector<Edge> edgeList;

  std::vector<EdgeID> getEdges(VertexID endVertex, VertexID startVertex); // returns a list of all edges between two vertices.

  Graph(std::vector<Vertex> vertexList, std::vector<Edge> edgeList);
};
