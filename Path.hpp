#pragma once

#include "util.hpp"
//#include "Graph.hpp"

#include <vector>

class Path
{
public:
  const std::vector<EdgeID>& getEdgeList() const { return mPath; }; // needed to access the edge list nonlocally

  size_t length() const { return mPath.size(); }

  Path(Graph& graph, std::vector<EdgeID> edgeList, bool checkValidity = false)
  {
    // verify edgeList is not empty and verify its a valid path
  }

  Path(Graph& graph, VertexID vertexID)
  {
    // single vertex
  }

  Path(Graph& graph) // case of the zero path
    : mGraph(graph),
      mIsZero(true),
      mIsVertex(false),
      mStartVertex(-1),
      mEndVertex(-1),
      mPathID(0),
      mPath({})
  {
    
  }
  
private:
  Graph& mGraph;
  bool mIsZero;
  bool mIsVertex;
  VertexID mStartVertex;
  VertexID mEndVertex;
  PathID mPathID;
  std::vector<EdgeID> mPath;
};
