#include "Graph.hpp"

Vertex::Vertex(VertexID id, std::string label)
   : vertexID(id),
     vertexLabel(label)
{
}

Edge::Edge(EdgeID id, EdgeLabel label, VertexID start, VertexID end, std::vector<int> weight)
   : edgeID(id),
     edgeLabel(label),
     startVertexID(start),
     endVertexID(end),
     edgeWeight(weight)
{
}

Edge::Edge(EdgeID id, EdgeLabel label, VertexID start, VertexID end)
   : edgeID(id),
     edgeLabel(label),
     startVertexID(start),
     endVertexID(end),
     edgeWeight({})
{
}

std::vector<int> Edge::getWeight() {
  return edgeWeight;
}

/*
 * This function takes in an adjacency matrix and constructs a graph based on it
 * TODO Need to implement label vectors, currently using empty label placeholders
 */

// dense adjacency matrix constructor
Graph::Graph(std::vector<std::vector<int>> adjMatrix)
{
  // Make sure we have square matrix, otherwise exit program
  
  // TODO Write error handler for this.
  if(adjMatrix.size() != adjMatrix[1].size())
    exit(1);

  int edgeIndex = 0;
  for(int i = 0; i < adjMatrix.size(); i++)
  {
    vertexList.push_back(Vertex(i, ""));

    for(int j = 0; j < adjMatrix[i].size();j++)
      for(int k = 0; k < adjMatrix[i][j];k++)
        edgeList.push_back(Edge(EdgeID(edgeIndex++), "", VertexID(i), VertexID(j)));
  }

}

// sparse adjacency matrix constructor (TODO: fix?)
Graph::Graph(std::vector<std::vector<std::pair<int, int>>> adjMatrix)
{
  // Make sure we have square matrix, otherwise exit program
  
  int edgeIndex = 0;
  for(int i = 0; i < adjMatrix.size(); i++)
  {
    // TODO Write error handler for this.
    if(adjMatrix.size() > adjMatrix[1].size())
      exit(1);

    vertexList.push_back(Vertex(i, ""));

    for(int j = 0; j < adjMatrix[i].size();j++)
      for(int k = 0; k < adjMatrix[i][j].second;k++)
        edgeList.push_back(Edge(EdgeID(edgeIndex++), "", VertexID(i), VertexID(j)));
  }
  // buildVertexList(vertexList, vertLabels);
  // buildEdgeList(edgeList, edgeLabels);

}

void buildVertexList(std::vector<Vertex>& vertList, std::vector<string> vertLabels)
{
   
}

std::vector<string> buildVertexLabels(int numVertices)
{
}

std::vector<string> buildVertexLabels(std::string baseName, int numVertices)
{
}


// function to convert sparse matrix to dense matrix
// functions which build vectors with labels of vertices and edges
// function which sets all members for graph object (adjMatrix, vertex labels, edge labels)

