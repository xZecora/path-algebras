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

   Path path_a(0,0,{0});
   Path path_b(0,0,{2});
   Path path_c(0,0,{3});
   Path path_d(0,0,{1});

   PathID path_cdab = myPathAlgebra.multiplyPaths(myPathAlgebra.multiplyPaths(path_c, path_d), myPathAlgebra.multiplyPaths(path_a,path_b));
   PathID path_cb = myPathAlgebra.multiplyPaths(path_c, path_b);
   PathID path_bc = myPathAlgebra.multiplyPaths(path_b, path_c);
   PathID path_da = myPathAlgebra.multiplyPaths(path_d, path_a);

   PAElement cdab(path_cdab);
   PAElement cb(path_cb);

   PAElement leftPoly;
   myPathAlgebra.subtract(leftPoly, cdab, cb);

   PAElement bc(path_bc);
   PAElement da(path_da);
   PAElement rightPoly;
   myPathAlgebra.subtract(rightPoly, bc, da);

   std::vector<PAElement> example = {leftPoly,rightPoly};
   auto exampleGB = myPathAlgebra.Buchbergers(example, 20);

   for (auto f : exampleGB){
        myPathAlgebra.printPAElementByLabel(std::cout, f);
	      std::cout << std::endl << std::flush;
   }
}
