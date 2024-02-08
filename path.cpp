#import <vector>
#import <unordered_map>

class Vertex{
  int id;
  std::vector<Vertex*> adjList;

  public:
    Vertex(int id) {
      this->id = id;
      adjList = std::vector<Vertex*>();
    }

    void addAdj(Vertex* v) {
      adjList.push_back(v);
    }
};

class Edge{
  int id;
  Vertex *start, *end;
  std::vector<Edge*> adjList;

  public:
    Edge(int id, Vertex *start, Vertex *end) {
      adjList = std::vector<Edge*>();
      this->id = id;
      this->start = start;
      this->end = end;
    }
};

class PathAlgebra {

  std::unordered_map<int, Vertex> vertices;
  std::unordered_map<int, Edge> edges;

  public:
    PathAlgebra(int len, int adjMatrix[3][3]) {
      int eCount = 0;

      for(int i=0;i<len;i++){

        vertices[i] = Vertex(i);
      }

      for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
          if(adjMatrix[i][j] == 1) {

            edges[eCount++] = Edge(eCount, &vertices[i], &vertices[j]);
          }
        }
      }
    }

};

int main() {
  int adjMatrix[3][3] = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};

  PathAlgebra pathAlg = PathAlgebra(3, adjMatrix);
}
