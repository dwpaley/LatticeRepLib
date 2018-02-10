// ConvertToC3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

#include "C3.h"
#include "LRL_ReadLatticeData.h"
#include "LRL_StringTools.h"
#include "LRL_ToString.h"


std::string Letters(void) {
   return "V,D,S,P,A,B,C,I,F,R";
}

std::vector<LRL_ReadLatticeData> GetInputCells(void) {
   const std::string letters = Letters();
   std::string lattice;
   std::vector<LRL_ReadLatticeData> cellDataList;
   while (lattice != "EOF") {
      LRL_ReadLatticeData rcd;
      lattice = rcd.GetLattice();
      const size_t quest = letters.find(lattice);
      if ((!lattice.empty()) && (letters.find(toupper(lattice[0])) != std::string::npos))
         cellDataList.push_back(rcd);
   }

   return cellDataList;
}

int main()
{
   const std::vector<LRL_ReadLatticeData> cellDataList = GetInputCells();

   for ( unsigned long i=0; i<cellDataList.size(); ++i ) {
      std::cout << cellDataList[i].GetStrCell() << "   " << C3(cellDataList[i].GetCell()) << std::endl;
   }

    return 0;
}

