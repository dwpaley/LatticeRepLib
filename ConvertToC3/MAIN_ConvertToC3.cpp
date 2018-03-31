// ConvertToC3.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <vector>

#include "C3.h"
#include "D7.h"
#include "G6.h"
#include "LRL_Cell.h"
#include "LRL_Cell_Degrees.h"
#include "LRL_ReadLatticeData.h"
#include "LRL_StringTools.h"
#include "LRL_ToString.h"
#include "S6Dist.h"
#include "Selling.h"


std::string Letters(void) {
   return "V,D,S,P,A,B,C,I,F,R,C3";
}

std::vector<LRL_ReadLatticeData> GetInputCells(void) {
   const std::string letters = Letters();
   std::string lattice;
   std::vector<LRL_ReadLatticeData> cellDataList;
   LRL_ReadLatticeData rcd;
   while (lattice != "EOF") {
      rcd.read();
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
      std::cout << cellDataList[i].GetStrCell() << "                                 " << C3(cellDataList[i].GetCell()) << std::endl;
      S6 red;
      const bool b = Selling::Reduce(S6(cellDataList[i].GetCell()), red);
      std::cout <<" " << red << "                              $   " << C3(red) << std::endl << std::endl;
   }

   for (unsigned long i = 0; i<cellDataList.size(); ++i) {
      const S6       s6(cellDataList[i].GetCell());
      const C3       c3(cellDataList[i].GetCell());
      const D7       d7(cellDataList[i].GetCell());
      const G6       g6(cellDataList[i].GetCell());
      const LRL_Cell cl(cellDataList[i].GetCell());

      std::cout <<       S6::GetName() << "  " << C3(s6) << std::endl;
      std::cout <<       C3::GetName() << "  " << C3(c3) << std::endl;
      std::cout <<       D7::GetName() << "  " << C3(d7) << std::endl;
      std::cout <<       G6::GetName() << "  " << C3(g6) << std::endl;
      std::cout << LRL_Cell::GetName() << "  " << C3(cl) << std::endl;
      std::cout << std::endl;
   }


    return 0;
}

