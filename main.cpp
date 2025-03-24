#include <iostream>
#include "Field.hpp"
#include "Graph.hpp"
#include "PathAlgebra.hpp"
#include "PAElement.hpp"

#include <chrono>

int main(int argc, char** argv)
{
   FieldElement a { 10 };
   FieldElement b { 4 };
   FieldElement one { 1 };

   Field myField { 101 };
   FieldElement minus_one = myField.negate(one);

   std::cout << "Field element a: " << a << std::endl;
   std::cout << "a to the power 15 in field: " << myField.power(a,15)
             << std::endl;

   //Graph myGraph({ std::vector<int> {1} });
   //Graph myGraph({{1,2,3},{1,2,3},{1,2,3}});

   Graph myGraph({{1,1,0},{0,1,1},{0,0,1}}, {"vertex1", "vertex2", "vertex3"}, {"edge1", "edge2", "edge3", "edge4", "edge5"});
   Graph myGraph2({ std::vector<int> {3} }, {"v0"}, {"x","y","z"});

   std::vector<WeightVector> weights = {{1},{2},{3},{2},{1}};
   std::vector<WeightVector> weights2 = {{1},{1},{1}};

   PathOrder myPathOrder(weights);
   PathOrder pathOrder2(weights2);

   std::cout << std::endl << std::flush;

   PathAlgebra myPathAlgebra(myGraph, myField, myPathOrder);
   // PathAlgebra myPathAlgebra2(myGraph2, myField, pathOrder2);
   PathAlgebra myPathAlgebra2(myGraph2, myField);

   Path myPath(0,0,{0,0,0,0,0});
   Path myPath2(1,2,{0,1,2,3,4});   // not a valid path... should we error?
   Path myPath3(0,2,{0,1,2,3,4});
   // myGraph.isValid(myPath);  // should (be implemented) and return true
   // myGraph.isValid(myPath2);  // should (be implemented) and return false
   // myGraph.isValid(myPath3);  // should (be implemented) and return true

   myPathAlgebra.addToPathTable(myPath);

   std::cout << myGraph.printEdgeID(myPath) << std::endl;
   std::cout << myGraph.printPathByLabel(myPath) << std::endl;
   std::cout << myGraph.printPathByLabel(myPath2) << std::endl;

   PathID multPath1 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath2 = myPathAlgebra.multiplyPaths(myPath,myPath);
   PathID multPath3 = myPathAlgebra.multiplyPaths(myPath,myPath3);

   PAElement monom1(multPath1);
   PAElement monom2(multPath1, FieldElement { 2 });
   PAElement monom3(multPath3);

   PAElement mySum1, mySum2;
   myPathAlgebra.add(mySum1,monom1,monom2);
   myPathAlgebra.add(mySum2,monom1,monom3);


   myPathAlgebra.printPAElementByLabel(std::cout, mySum1);
   std::cout << std::endl;
   myPathAlgebra.printPAElementByLabel(std::cout, mySum2);
   std::cout << std::endl;

   PAElement mySum3;
   myPathAlgebra.subtract(mySum3, mySum1, mySum1);
   myPathAlgebra.printPAElementByLabel(std::cout, mySum3);
   std::cout << std::endl << std::flush;

   Path path_x(0,0,{0});
   Path path_y(0,0,{1});
   Path path_z(0,0,{2});
   Path vert(0);

   // should make PathAlgebra method which takes a path and
   // returns a PAElement (creating PathID if necessary)
   // insertInDictionary?
   PathID id_x = myPathAlgebra2.multiplyPaths(vert,path_x);  
   PathID id_y = myPathAlgebra2.multiplyPaths(vert,path_y);
   PathID id_z = myPathAlgebra2.multiplyPaths(vert,path_z);
   PathID id_vert = myPathAlgebra2.multiplyPaths(vert,vert);
   PathID id_x2 = myPathAlgebra2.multiplyPaths(id_x,id_x);
   PathID id_y2 = myPathAlgebra2.multiplyPaths(id_y,id_y);
   PathID id_z2 = myPathAlgebra2.multiplyPaths(id_z,id_z);
   PathID id_xy = myPathAlgebra2.multiplyPaths(id_x,id_y);
   PathID id_yx = myPathAlgebra2.multiplyPaths(id_y,id_x);
   PathID id_xz = myPathAlgebra2.multiplyPaths(id_x,id_z);
   PathID id_zx = myPathAlgebra2.multiplyPaths(id_z,id_x);
   PathID id_yz = myPathAlgebra2.multiplyPaths(id_y,id_z);
   PathID id_zy = myPathAlgebra2.multiplyPaths(id_z,id_y);
   PathID id_xyxy = myPathAlgebra2.multiplyPaths(id_xy,id_xy);
   PathID id_xyxyx2 = myPathAlgebra2.multiplyPaths(id_xyxy,id_x2);

   std::cout << "id_vert" << id_vert << std::endl;

   PAElement elt_v(id_vert);
   PAElement elt_x(id_x);
   PAElement elt_y(id_y);
   PAElement elt_xy(id_xy);
   PAElement elt_yx(id_yx);
   PAElement elt_xz(id_xz);
   PAElement elt_zx(id_zx);
   PAElement elt_yz(id_yz);
   PAElement elt_zy(id_zy);
   PAElement elt_x2(id_x2);
   PAElement elt_xyxy(id_xyxy);
   PAElement elt_xyxyx2(id_xyxyx2);
   PAElement elt_comm_x_y;
   PAElement elt_comm_x_z;
   PAElement elt_comm_y_z;
   PAElement toReduce;
   PAElement f1({id_x2,id_yz,id_zy},{FieldElement(1),FieldElement(3),FieldElement(7)});
   PAElement f2({id_xz,id_y2,id_zx},{FieldElement(1),FieldElement(29),FieldElement(87)});
   PAElement f3({id_xy,id_yx,id_z2},{FieldElement(1),FieldElement(36),FieldElement(34)});
   myPathAlgebra2.subtract(elt_comm_x_y,elt_xy,elt_yx);
   myPathAlgebra2.subtract(elt_comm_x_z,elt_xz,elt_zx);
   myPathAlgebra2.subtract(elt_comm_y_z,elt_yz,elt_zy);
   myPathAlgebra2.add(toReduce,elt_xyxy,elt_xyxyx2);

   std::vector<PAElement> commGens = {elt_comm_x_y, elt_comm_x_z, elt_comm_y_z};
   std::vector<PAElement> sklyGens = {f1,f2,f3};
   
   auto commGensGB = myPathAlgebra2.Buchbergers(commGens, 10, 10);
   for (auto f : commGensGB)
   {
        myPathAlgebra2.printPAElementByLabel(std::cout, f);
	std::cout << std::endl << std::flush;
   }

   auto sklyGensGB = myPathAlgebra2.Buchbergers(sklyGens, 5, 5);
   for (auto f : sklyGensGB)
   {
        myPathAlgebra2.printPAElementByLabel(std::cout, f);
	std::cout << std::endl << std::flush;
   }

   PAElement sumxy;
   PAElement zeroPA(0);
   myPathAlgebra2.add(sumxy,id_x,id_y);
   PAElement expXplusY;
   PAElement expXplusYSC;
   PAElement bigMult;
   myPathAlgebra2.exponent(expXplusY,sumxy,7);
   myPathAlgebra2.exponentSC(expXplusY,sumxy,7);

   //auto startTime = std::chrono::high_resolution_clock::now();
   //myPathAlgebra2.multiply(bigMult,expXplusY,expXplusY);
   //auto endTime = std::chrono::high_resolution_clock::now();

   //auto duration = duration_cast<std::chrono::milliseconds>(endTime-startTime);
   //std::cout << "Duration for big multiplication: " << duration.count() << "ms" << std::endl;

   myPathAlgebra2.printPAElementByLabel(std::cout, elt_v);
   std::cout << std::endl;
   myPathAlgebra2.printPAElementByPathID(std::cout, elt_v);
   std::cout << std::endl;
   myPathAlgebra2.printPAElementByLabel(std::cout, sumxy);
   std::cout << std::endl;
   myPathAlgebra2.printPAElementByPathID(std::cout, sumxy);
   std::cout << std::endl;
   myPathAlgebra2.printPAElementByPathID(std::cout, elt_x2);
   std::cout << std::endl;
   myPathAlgebra2.printPAElementByPathID(std::cout, zeroPA);
   std::cout << std::endl;
   //myPathAlgebra2.printPAElementByLabel(std::cout, expXplusY);
   //std::cout << std::endl;

   myPathAlgebra2.printPathTable();

   auto myPair = myPathAlgebra2.isAnySubword({id_x}, id_xy);
   std::cout << myPair.first << " " << myPair.second << std::endl;

   myPair = myPathAlgebra2.isAnySubword({id_y}, id_xy);
   std::cout << myPair.first << " " << myPair.second << std::endl;

   myPair = myPathAlgebra2.isAnySubword({id_x2, id_yx}, id_xyxy);
   std::cout << myPair.first << " " << myPair.second << std::endl;

   myPathAlgebra2.printPAElementByLabel(std::cout, myPathAlgebra2.dividePAElement({elt_comm_x_y}, elt_xyxy));
   std::cout << std::endl << std::flush;
   myPathAlgebra2.printPAElementByLabel(std::cout, myPathAlgebra2.dividePAElement({elt_comm_x_y}, toReduce));
   std::cout << std::endl << std::flush;

   return 0;
}
