// ReductionTimeingTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "D7.h"
#include "Delone.h"
#include "G6.h"
#include "GenerateRandomLattice.h"
#include "LatticeConverter.h"
#include "LRL_Cell.h"
#include "LRL_Cell_Degrees.h"
#include "LRL_ReadLatticeData.h"
#include "Niggli.h"
#include "NullOps.h"
#include "S6.h"

template<typename VEC1, typename METHOD1>
VEC1 TestTiming(const unsigned long count, const std::vector<std::string> vstr, const std::vector<S6> vin) {
   LatticeConverter converter;
   LRL_Cell dummy;
   std::clock_t start;
   std::vector<LRL_Cell> vcell;
   std::list<LRL_Cell>::iterator itcell;

   VEC1 red1;
   for (unsigned long i = 0; i < vin.size(); ++i) vcell.push_back(vin[i]);

   LRL_Cell cellP;
   {
      start = std::clock();
      for (unsigned long i = 0; i < vcell.size(); ++i ) {
         const LRL_Cell cell = converter.MakePrimitiveCell(vstr[i], vcell[i]);
         const bool b = METHOD1::Reduce(VEC1(cellP), red1);
         dummy = red1;
      }

      dummy *= 2.0; // to try to get the optimizer to keep calculating dummy as unit cell parmeters
      std::cout << std::endl;
      std::cout << VEC1::GetName() << "  " << METHOD1::GetName() << "  " << std::clock() - start << " msec" << std::endl;
   }

   return dummy;
}

template<typename VEC1, typename METHOD1, typename VEC2, typename METHOD2>
VEC2 TestTiming(const unsigned long count, const std::vector<std::string> vstr, const std::vector<S6> vin) {
   LatticeConverter converter;
   LRL_Cell dummy;
   std::clock_t start;
   std::vector<LRL_Cell> vcell;
   std::list<LRL_Cell>::iterator itcell;

   VEC1 red1;
   VEC2 red2;
   for (unsigned long i = 0; i < vin.size(); ++i) vcell.push_back(vin[i]);

   LRL_Cell cellP;
   {
      start = std::clock();
      for (unsigned long i = 0; i < vcell.size(); ++i) {
         const LRL_Cell cell = converter.MakePrimitiveCell(vstr[i], vcell[i]);
         const bool b = METHOD1::Reduce(VEC1(cellP), red1);
         dummy = red1;
         const bool b2 = METHOD2::Reduce(VEC2(red1), red2);
         dummy = red2;
      }
   }

   dummy *= 2.0; // to try to get the optimizer to keep calculating dummy as unit cell parmeters
   std::cout << std::endl;
   std::cout << "Vector type1 " << VEC1::GetName() << "   Reduction method1  " << METHOD1::GetName() << std::endl <<
      "Vector type2 " << VEC2::GetName() << "   Reduction method2  " << METHOD2::GetName() << "  " << std::clock() - start << " msec" << std::endl;

   return dummy;
}

std::string Letters(void) {
   return "V,G,D,S,P,A,B,C,I,F,R,C3,G6,S6,B4,D7,H";
}

std::vector<LRL_ReadLatticeData> GetInputCells(void) {
   const std::string letters = Letters();
   std::string lattice;
   std::vector<LRL_ReadLatticeData> cellDataList;
   LRL_ReadLatticeData rcd;
   while (lattice != "EOF") {
      rcd.read();
      lattice = rcd.GetLattice();
      if ((!lattice.empty()) && (letters.find(toupper(lattice[0])) != std::string::npos))
         cellDataList.push_back(rcd);
   }

   return cellDataList;
}

void TestRandomGeneration() {
   std::vector<S6> v;
   std::vector<std::string> vstr;
   int seed = 19191;
   GenerateRandomLattice<S6> grl(seed);
   unsigned long count = 100000;
   std::cout << "samples generated " << count << "    S6::randDeloneReduced()" << std::endl;
   for (unsigned long i = 0; i < count; ++i) {
      v.push_back(S6::randDeloneReduced());
      vstr.push_back("P");
   }

   TestTiming<G6, Niggli >(1, vstr, v); //A
   TestTiming<D7, Delone >(1, vstr, v); //B
   TestTiming<S6, Selling>(1, vstr, v); //C

   TestTiming<G6, Selling, G6, Niggli >(0, vstr, v); //D
   TestTiming<D7, Selling, S6, Delone >(0, vstr, v); //E
   TestTiming<S6, Selling, S6, Selling>(0, vstr, v); //F
}

void TestPDBCells() {
   std::cout << "PDB Cells input " << < std::endl;
   const std::vector<LRL_ReadLatticeData> input = GetInputCells();
   std::vector<S6> v;
   std::vector<std::string> vstr;
   for (unsigned long i = 0; i < input.size(); ++i) {
      v.push_back(input[i].GetCell());
      vstr.push_back(input[i].GetLattice());
   }

   TestTiming<G6, Niggli >(1, vstr, v); //A
   TestTiming<D7, Delone >(1, vstr, v); //B
   TestTiming<S6, Selling>(1, vstr, v); //C

   TestTiming<G6, Selling, G6, Niggli >(0, vstr, v); //D
   TestTiming<D7, Selling, S6, Delone >(0, vstr, v); //E
   TestTiming<S6, Selling, S6, Selling>(0, vstr, v); //F
}

int main(int argc, char *argv[])
{
   TestPDBCells();
   TestRandomGeneration();

}

