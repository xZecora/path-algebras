#include "Graph.hpp"

Vertex::Vertex(VertexID id, std::string name) : vertexID(id), vertexLabel(name) {}
Edge::Edge(EdgeID id, EdgeLabel label, VertexID start, VertexID end) : edgeID(id), edgeLabel(label), startVertexID(start), endVertexID(end) {}

int Edge::getWeight() {
  return weight;
}
