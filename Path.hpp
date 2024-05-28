#pragma once

#include "util.hpp"
#include "Graph.hpp"
#include <vector>

class Path
{
friend class PathHash;
public:
  const std::vector<EdgeID>& getEdgeList() const { return mPath; }; // needed to access the edge list nonlocally

  size_t length() const { return mPath.size(); }

  Path(Graph& graph, std::vector<EdgeID> pathEdgeList, bool checkValidity = false)
    : mGraph(graph),
      mIsZero(false),
      mIsVertex(false),
      mStartVertex(graph.getStartVertex(pathEdgeList[0])),
      mEndVertex(graph.getEndVertex(pathEdgeList[pathEdgeList.size()-1])),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath(pathEdgeList)
  {
    // creator of this object should verify edgeList is not empty and 
    // that it is a valid path
  }

  Path(Graph& graph, VertexID vertexID)
    : mGraph(graph),
      mIsZero(false),
      mIsVertex(true),
      mStartVertex(vertexID),
      mEndVertex(vertexID),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath({})
  {
    // case of single vertex
    // creator of this object should ensure that vertex is valid
  }

  Path(Graph& graph) // case of the zero path
    : mGraph(graph),
      mIsZero(true),
      mIsVertex(false),
      mStartVertex(-1),
      mEndVertex(-1),
      mPathID(0),  // zero path should be first element in dictionary
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

class PathHash {
public:
  std::size_t operator()(const Path& p) const
  {
    std::size_t hash = 0;
    if (p.mIsZero) return hash;
    if (p.mIsVertex) {
      hash = p.mStartVertex;
      return hash;
    }
    for (auto e : p.mPath) 
    {
       hash += 12345*hash + e;
    }
    return hash;
  }
};

