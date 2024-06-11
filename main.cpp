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

   PathAlgebra myPathAlgebra(myGraph,myField);

   Path myPath(0,0,{0,0,0,0,0});

   Path multPath1 = myPathAlgebra.multiplyPaths(myPath,myPath);
   Path multPath2 = myPathAlgebra.multiplyPaths(myPath,myPath);

   std::cout << multPath1.printID() << std::endl;

   return 0;
}
