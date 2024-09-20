#include <iostream>
#include "Field.hpp"
#include "Graph.hpp"
#include "PathAlgebra.hpp"
#include "PAElement.hpp"

int main(int argc, char** argv)
{
   FieldElement a { 10 };
   FieldElement b { 4 };
   Field myField { 101 };

   std::cout << "Field element a: " << a << std::endl;
   std::cout << "a to the power 15 in field: " << myField.power(a,15)
             << std::endl;

   //Graph myGraph({ std::vector<int> {1} });
   //Graph myGraph({{1,2,3},{1,2,3},{1,2,3}});

   Graph myGraph({{1,1,0},{0,1,1},{0,0,1}}, {"vertex1", "vertex2", "vertex3"}, {"edge1", "edge2", "edge3", "edge4", "edge5"});

   std::vector<WeightVector> weights = {{1},{2},{3}};

   PathOrder myPathOrder(weights);

   std::cout << std::endl << std::flush;

   PathAlgebra myPathAlgebra(myGraph, myField, myPathOrder);

   Path myPath(0,0,{0,0,0,0,0});
   Path myPath2(1,2,{0,1,2,3,4});
   Path myPath3(0,2,{0,1,2,3,4});
   // myGraph.isValid(myPath);  // should (be implemented) and return true
   // myGraph.isValid(myPath2);  // should (be implemented) and return false
   // myGraph.isValid(myPath3);  // should (be implemented) and return true

   myPathAlgebra.addToPathTable(myPath);

   std::cout << myGraph.printEdgeID(myPath) << std::endl;
   std::cout << myGraph.printEdgeLabel(myPath) << std::endl;
   std::cout << myGraph.printEdgeLabel(myPath2) << std::endl;

   PathID multPath1 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath2 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath3 = myPathAlgebra.multiplyPaths(myPath,myPath3);

   std::cout << "PathID1: " << multPath1 << std::endl;
   std::cout << "PathID2: " << multPath2 << std::endl;
   std::cout << "PathID3: " << multPath3 << std::endl;

   PAElement monom1(multPath1);
   PAElement monom2(multPath1, FieldElement { 2 });
   PAElement monom3(multPath3);

   std::cout << "Entering sum code." << std::endl;
   PAElement mySum1, mySum2;
   myPathAlgebra.add(mySum1,monom1,monom2);
   myPathAlgebra.add(mySum2,monom1,monom3);

   return 0;
}
