#include <sstream>
#include <string>
#include "Graph.hpp"

// adjMatrix is the dense representation of the data
void buildVerticesAndEdges(std::vector<std::vector<int>> adjMatrix,
			   std::vector<Vertex>& vertList,
			   std::vector<Edge>& edgeList,
			   const std::vector<std::string>& vertLabels,
			   const std::vector<std::string>& edgeLabels)
{
  int edgeIndex = 0;
  for(int i = 0; i < adjMatrix.size(); i++)
  {
    // Make sure we have square matrix, otherwise exit program
    // TODO Write error handler for this.
    if(adjMatrix.size() != adjMatrix[i].size())
      exit(1);

    vertList.push_back(Vertex(i, vertLabels[i]));

    for(int j = 0; j < adjMatrix[i].size(); j++){
      for(int k = 0; k < adjMatrix[i][j]; k++){
        edgeList.push_back(Edge(EdgeID(edgeIndex), edgeLabels[edgeIndex], VertexID(i), VertexID(j)));
        edgeIndex++;
      }
    }
  }
}

std::vector<std::string> buildLabels(int numLabels, std::string baseName){
  std::vector<std::string> result;
  for(int i = 0; i < numLabels; ++i)
  {
    std::basic_ostringstream<char> buf;
    buf << baseName << i+1;
    result.push_back(buf.str());
  }
  return result;
}

std::vector<std::string> buildVertexLabels(int numVertices)
{
  return buildLabels(numVertices, "v");
}
std::vector<std::string> buildEdgeLabels(int numEdges)
{
  return buildLabels(numEdges, "e");
}

std::vector<std::string> buildVertexLabels(int numVertices, std::string baseName)
{
  return buildLabels(numVertices, baseName);
}

std::vector<std::string> buildEdgeLabels(int numEdges, std::string baseName)
{
  return buildLabels(numEdges, baseName);
}

/*
std::vector<std::string> buildVertexLabels(int numVertices)
{
  std::vector<std::string> result;
  std::basic_ostringstream<char> buf;
  for(int i = 0; i < numVertices; ++i)
  {
    buf << "v" << i+1;
    result.push_back(buf.str());
  }
  return result;
}

std::vector<std::string> buildVertexLabels(std::string baseName, int numVertices)
{
  std::vector<std::string> result;
  std::basic_ostringstream<char> buf;
  for(int i = 0; i < numVertices; ++i)
  {
    buf << baseName << i+1;
    result.push_back(buf.str());
  }
  return result;
}

std::vector<std::string> buildEdgeLabels(int numEdges)
{
  std::vector<std::string> result;
  std::basic_ostringstream<char> buf;
  for(int i = 0; i < numEdges; ++i)
  {
    buf << "e" << i+1;
    result.push_back(buf.str());
  }
  return result;
}

std::vector<std::string> buildEdgeLabels(std::string baseName, int numEdges)
{
  std::vector<std::string> result;
  std::basic_ostringstream<char> buf;
  for(int i = 0; i < numEdges; ++i)
  {
    buf << baseName << i+1;
    result.push_back(buf.str());
  }
  return result;
}
*/

// Vertex class members

Vertex::Vertex(VertexID id, std::string label)
   : vertexID(id),
     vertexLabel(label)
{
}

// Edge class members

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

// Graph class members

/*
 * This function takes in a sparse matrix and converts it to a dense matrix for all of our logic purposes
 */
std::vector<std::vector<int>> sparseToDense(const std::vector<std::vector<std::pair<int, int>>>& sparseMatrix)
{
  std::vector<std::vector<int>> denseMatrix = {};
  for(int i = 0; i < sparseMatrix.size(); ++i)
    denseMatrix.push_back(std::vector<int>(sparseMatrix.size()));

  int i = 0;
  for(auto it = sparseMatrix.begin(); it != sparseMatrix.end(); it++, ++i){
    for(auto jt = it->begin(); jt!=it->end(); jt++){
      denseMatrix[i][jt->first] = jt->second;
    }
  }

  return denseMatrix;
}

/*
 * This function takes in an adjacency matrix and constructs a graph based on it
 * TODO Need to implement label vectors, currently using empty label placeholders
 */

// dense adjacency matrix constructor
Graph::Graph(const std::vector<std::vector<int>>& adjMatrix)
{
  std::vector<std::string> vertexLabels = buildVertexLabels(adjMatrix.size());

  int numEdges = 0;
  for(int i = 0; i < adjMatrix.size(); ++i)
    for(int j = 0; j < adjMatrix[i].size(); ++j)
      numEdges += adjMatrix[i][j];

  std::vector<std::string> edgeLabels = buildEdgeLabels(numEdges);

  buildVerticesAndEdges(adjMatrix,vertexList,edgeList,vertexLabels,edgeLabels);
}

Graph::Graph(const std::vector<std::vector<int>>& adjMatrix, const std::vector<std::string>& vertexLabels, const std::vector<std::string>& edgeLabels)
{
  int numEdges = 0;
  for(int i = 0; i < adjMatrix.size(); ++i)
    for(int j = 0; j < adjMatrix[i].size(); ++j)
      numEdges += adjMatrix[i][j];

  if (numEdges != edgeLabels.size())
    exit(0);

  buildVerticesAndEdges(adjMatrix,vertexList,edgeList,vertexLabels,edgeLabels);
}

// sparse adjacency matrix constructor (TODO: fix?)
Graph::Graph(const std::vector<std::vector<std::pair<int, int>>>& sparseAdjMatrix)
{
  // adjMatrix is the dense representation of the sparse input
  std::vector<std::vector<int>> adjMatrix = sparseToDense(sparseAdjMatrix);
  
  std::vector<std::string> vertexLabels = buildVertexLabels(adjMatrix.size());

  int numEdges = 0;
  for(int i = 0; i < adjMatrix.size(); ++i)
    for(int j = 0; j < adjMatrix[i].size(); ++j)
      numEdges += adjMatrix[i][j];

  std::vector<std::string> edgeLabels = buildEdgeLabels(numEdges);

  buildVerticesAndEdges(adjMatrix,vertexList,edgeList,vertexLabels,edgeLabels);  
}

Graph::Graph(const std::vector<std::vector<std::pair<int, int>>>& sparseAdjMatrix, const std::vector<std::string>& vertexLabels, const std::vector<std::string>& edgeLabels)
{
  // adjMatrix is the dense representation of the sparse input
  std::vector<std::vector<int>> adjMatrix = sparseToDense(sparseAdjMatrix);
  
  //std::vector<std::string> vertexLabels = buildVertexLabels(adjMatrix.size());

  int numEdges = 0;
  for(int i = 0; i < adjMatrix.size(); ++i)
    for(int j = 0; j < adjMatrix[i].size(); ++j)
      numEdges += adjMatrix[i][j];

  if (numEdges != edgeLabels.size())
    exit(0);

  //std::vector<std::string> edgeLabels = buildEdgeLabels(numEdges);

  buildVerticesAndEdges(adjMatrix,vertexList,edgeList,vertexLabels,edgeLabels);  
}
