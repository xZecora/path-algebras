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

  Path(VertexID startVertex,
       VertexID endVertex,
       std::vector<EdgeID> pathEdgeList,
       bool checkValidity = false)
    : mIsZero(false),
      mIsVertex(false),
      mStartVertex(startVertex),
      mEndVertex(endVertex),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath(pathEdgeList)
  {
  }

  Path(VertexID vertexID)
    : mIsZero(false),
      mIsVertex(true),
      mStartVertex(vertexID),
      mEndVertex(vertexID),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath({})
  {
  }

  Path() // case of the zero path
    : mIsZero(true),
      mIsVertex(false),
      mStartVertex(-1),
      mEndVertex(-1),
      mPathID(0),  // zero path should be first element in dictionary
      mPath({})
  {
  }

  bool std::operator==(const Path p, const Path q) 
  {
    return (p.mPathID == q.mPathID);
  }
  
private:
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

