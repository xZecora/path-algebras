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

   Graph myGraph({{1}});

   PathAlgebra myPathAlgebra(myGraph,myField);

   return 0;
}
