#pragma once

#include "Path.hpp"
#include "util.hpp"
#include <vector>
#include <iostream>

class Vertex{
  friend class Graph;

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
  //std::vector<int> edgeWeight; // Need to store this to reference elsewhere

  public: 
  //Edge(EdgeID id, EdgeLabel label, VertexID startVertexID, VertexID endVertexID, std::vector<int> weight);
  Edge(EdgeID id, EdgeLabel label, VertexID startVertexID, VertexID endVertexID);

  //std::vector<int> getWeight(); // need to access weight nonlocally
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
  Graph(const std::vector<std::vector<int>>& adjMatrix, const std::vector<std::string>& vertexLabels, const std::vector<std::string>& edgeLabels);

  Graph(const std::vector<std::vector<std::pair<int, int>>>& sparseAdjMatrix);
  Graph(const std::vector<std::vector<std::pair<int, int>>>& sparseAdjMatrix, const std::vector<std::string>& vertexLabels, const std::vector<std::string>& edgeLabels);

  std::vector<EdgeID> getEdges(VertexID endVertex, VertexID startVertex); // returns a list of all edges between two vertices.

  VertexID getStartVertex(EdgeID edgeID) const { return edgeList[edgeID].startVertexID; }
  VertexID getEndVertex(EdgeID edgeID) const { return edgeList[edgeID].endVertexID; }

  std::string printPathByLabel(const Path& path) const
  {
    std::string output = "";
    int i = 0;
    for(EdgeID itr: path.getPathList()) {
      if(i+1 == path.getPathList().size()){
        output.append(edgeList[itr].edgeLabel);
      } else {
        output.append(edgeList[itr].edgeLabel + ", ");
      }
      i++;
    }
    if (i == 0) output.append(vertexList[path.getStartVertex()].vertexLabel);
    std::cout << "Start Vert: " << path.getStartVertex() << "  End" << std::endl << std::flush;
    return output;
  }

  std::string printEdgeID(const Path& path) const
  {
    return path.printEdgeID();
  }
};
