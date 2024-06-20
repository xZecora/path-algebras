#include <iostream>
#include "Field.hpp"
#include "Graph.hpp"
#include "PathAlgebra.hpp"

int main(int argc, char** argv)
{
   FieldElement a { 10 };
   FieldElement b { 4 };
   Field myField { 101 };

   std::cout << "Field element a: " << a << std::endl;
   std::cout << "a to the power 15 in field: " << myField.power(a,15)
             << std::endl;

   //Graph myGraph({ std::vector<int> {1} });
   Graph myGraph({{1,2,3},{1,2,3},{1,2,3}});

   for(auto itr: myGraph.edgeList){
      std::cout << itr.edgeLabel << std::endl;
   }

   PathAlgebra myPathAlgebra(myGraph, myField);

   Path myPath(0,0,{0,0,0,0,0});
   Path myPath2(1,2,{1,2,3,4,5});

   myPathAlgebra.addToPathTable(myPath);

   std::cout << myPath.printEdgeID() << std::endl;
   std::cout << myGraph.printEdgeLabel(myPath) << std::endl;
   std::cout << myGraph.printEdgeLabel(myPath2) << std::endl;

   PathID multPath1 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath2 = myPathAlgebra.multiplyPaths(myPath,myPath);

   std::cout << "PathID1: " << multPath1 << std::endl;
   std::cout << "PathID2: " << multPath2 << std::endl;

   return 0;
}
