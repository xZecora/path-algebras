#include <iostream>
#include "Field.hpp"
#include "Graph.hpp"
#include "PathAlgebra.hpp"
#include "PAElement.hpp"

#include <chrono>

int main(int argc, char** argv)
{
   Field myField { 101 };

   Graph myGraph({ std::vector<int> {3} }, {"v"}, {"x","y","z"});

   PathOrder myPathOrder({0,1,2});

   PathAlgebra myPathAlgebra(myGraph, myField, myPathOrder);

   Path path_x(0,0,{0});
   Path path_y(0,0,{1});
   Path path_z(0,0,{2});
   Path vert(0);

   PathID id_x2 = myPathAlgebra.multiplyPaths(path_x,path_x);
   PathID id_y2 = myPathAlgebra.multiplyPaths(path_y,path_y);
   PathID id_z2 = myPathAlgebra.multiplyPaths(path_z,path_z);
   PathID id_xy = myPathAlgebra.multiplyPaths(path_x,path_y);
   PathID id_yx = myPathAlgebra.multiplyPaths(path_y,path_x);
   PathID id_xz = myPathAlgebra.multiplyPaths(path_x,path_z);
   PathID id_zx = myPathAlgebra.multiplyPaths(path_z,path_x);
   PathID id_yz = myPathAlgebra.multiplyPaths(path_y,path_z);
   PathID id_zy = myPathAlgebra.multiplyPaths(path_z,path_y);

   std::cout << std::endl << "Generating sklyGens" << std::endl << std::flush;
   PAElement f1({id_x2,id_yz,id_zy},{FieldElement(1),FieldElement(3),FieldElement(7)});
   PAElement f2({id_xy,id_yx,id_z2},{FieldElement(1),FieldElement(36),FieldElement(34)});
   PAElement f3({id_xz,id_y2,id_zx},{FieldElement(1),FieldElement(29),FieldElement(87)});

   std::vector<PAElement> sklyGens = {f1,f2,f3};
   auto sklyGensGB = myPathAlgebra.Buchbergers(sklyGens, 10);

   for (auto f : sklyGensGB){
        myPathAlgebra.printPAElementByLabel(std::cout, f);
	      std::cout << std::endl << std::flush;
   }
}
