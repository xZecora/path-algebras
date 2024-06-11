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

   std::cout << int(myPathAlgebra.mPathTable.mReversePathDictionary.contains(myPathAlgebra.multiplyPaths(myPath, myPath))) << std::endl;

   for(int i = 0; i < myPathAlgebra.mPathTable.mPathDictionary.size(); i++){
     std::cout << i << ": " << myPathAlgebra.mPathTable.mPathDictionary[i].printID() << std::endl;
   }

   PathHash hash;
   std::cout << "Path 1 hash: " << hash(myPathAlgebra.mPathTable.mPathDictionary[multPath1]) << std::endl;
   std::cout << "Path 2 hash: " << hash(myPathAlgebra.mPathTable.mPathDictionary[multPath2]) << std::endl;

   std::cout << "Are they equal: " << int(myPathAlgebra.mPathTable.mReversePathDictionary.key_eq()(myPathAlgebra.mPathTable.mPathDictionary[multPath1], myPathAlgebra.mPathTable.mPathDictionary[multPath2])) << std::endl;

   std::cout << "Path 1 hash: " << myPathAlgebra.mPathTable.mReversePathDictionary.hash_function()(myPathAlgebra.mPathTable.mPathDictionary[multPath1]) << std::endl;
   std::cout << "Path 2 hash: " << myPathAlgebra.mPathTable.mReversePathDictionary.hash_function()(myPathAlgebra.mPathTable.mPathDictionary[multPath2]) << std::endl;

   std::cout << multPath1 << std::endl;
   std::cout << multPath2 << std::endl;

   return 0;
}
