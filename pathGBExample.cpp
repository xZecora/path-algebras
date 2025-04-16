#include <iostream>
#include "Field.hpp"
#include "Graph.hpp"
#include "PathAlgebra.hpp"
#include "PAElement.hpp"

#include <chrono>

int main(int argc, char** argv)
{
   Field myField { 101 };
   Graph myGraph({{0,1,0},{1,0,1},{0,1,0}}, {"v1","v2","v3"},{"a","d","b","c"});

   // adjacency matrix
   // 0 1 0
   // 1 0 1
   // 0 1 0  indexed row major

   PathOrder myOrder({1,4,2,3});

   PathAlgebra myPathAlgebra(myGraph, myField, myOrder);

   Path path_x(0,0,{0});
}
