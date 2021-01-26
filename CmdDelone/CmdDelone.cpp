
#include <iostream>

#include "LRL_ReadLatticeData.h"
#include "S6.h"
#include "Selling.h"

int main()
{
   const std::vector<LRL_ReadLatticeData> inputList = LRL_ReadLatticeData().ReadLatticeData();
   for (size_t i = 0; i < inputList.size(); ++i) {
      S6 s;
      const bool b = Selling::Reduce(inputList[i].GetCell(), s);
      std::cout << "Selling reduced" << s << std::endl;
   }
}
