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

   std::cout << myPath.printID() << std::endl;

   PathID multPath1 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath2 = myPathAlgebra.multiplyPaths(myPath,myPath);

   std::cout << "PathID1: " << multPath1 << std::endl;
   std::cout << "PathID2: " << multPath2 << std::endl;

   Path newPath1 = myPathAlgebra.mPathTable.mPathDictionary[multPath1];
   Path newPath2 = myPathAlgebra.mPathTable.mPathDictionary[multPath2];

   std::cout << "Contains1? " << myPathAlgebra.mPathTable.mReversePathDictionary.contains(newPath1) << std::endl;
   std::cout << "Contains2? " << myPathAlgebra.mPathTable.mReversePathDictionary.contains(newPath2) << std::endl;

   std::cout << myPathAlgebra.mPathTable.mReverseDictionary.size()

   return 0;
}
