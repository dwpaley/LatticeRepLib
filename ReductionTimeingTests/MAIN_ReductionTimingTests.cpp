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
#include "LRL_Cell.h"
#include "LRL_Cell_Degrees.h"
#include "Niggli.h"
#include "NullOps.h"
#include "S6.h"

template<typename VEC1, typename METHOD1>
VEC1 TestTiming(const unsigned long count, const std::vector<S6> vin) {
   LRL_Cell dummy;
   std::clock_t start;
   std::list<LRL_Cell> vcell;
   std::list<LRL_Cell>::iterator itcell;

   VEC1 red1;
   for (unsigned long i = 0; i < vin.size(); ++i) vcell.push_back(vin[i]);

   {
      start = std::clock();
      for (itcell = vcell.begin(); itcell != vcell.end(); ++itcell) {
         const bool b = METHOD1::Reduce(VEC1(*itcell), red1);
         dummy = red1;
      }



      dummy *= 2.0; // to try to get the optimizer to keep calculating dummy as unit cell parmeters
      std::cout << std::endl;
      std::cout << VEC1::GetName() << "  " << METHOD1::GetName() << "  " << std::clock() - start << " msec" << std::endl;
   }

   return dummy;
}

template<typename VEC1, typename METHOD1, typename VEC2, typename METHOD2>
VEC2 TestTiming(const unsigned long count, const std::vector<S6> vin) {
   LRL_Cell dummy;
   std::clock_t start;
   std::list<LRL_Cell> vcell;
   std::list<LRL_Cell>::iterator itcell;

   VEC1 red1;
   VEC2 red2;
   for (unsigned long i = 0; i < vin.size(); ++i) vcell.push_back(vin[i]);

   {
      start = std::clock();
      for (itcell = vcell.begin(); itcell != vcell.end(); ++itcell) {
         const bool b1 = METHOD1::Reduce(VEC1(*itcell), red1);
         dummy = red1;
         const bool b2 = METHOD2::Reduce(VEC2(red1), red2);
         dummy = red2;
      }
   }

   dummy *= 2.0; // to try to get the optimizer to keep calculating dummy as unit cell parmeters
      std::cout << std::endl;
      std::cout << "Vector type1 " <<VEC1::GetName() << "   Reduction method1  " << METHOD1::GetName() << std::endl <<
                   "Vector type2 " <<VEC2::GetName() << "   Reduction method2  " << METHOD2::GetName() <<"  " << std::clock() - start << " msec" << std::endl;

   return dummy;
}

int main(int argc, char *argv[])
{
   std::vector<S6> v;
   int seed = 19191;
   GenerateRandomLattice<S6> grl(seed);
   int count = 100000;
   std::cout << "samples generated " << count << "    S6::randDeloneReduced()" << std::endl;
   for ( unsigned long i=0; i< count; ++i ) {
      v.push_back(S6::randDeloneReduced());   
   }

   TestTiming<G6, Niggli>(1, v); //A
   TestTiming<D7, Delone>(1, v); //B
   TestTiming<S6, Selling>(1, v); //C

   TestTiming<G6, Selling,  G6, Niggli > (0, v);
   TestTiming<D7, Selling,  S6, Delone > (0, v);
   TestTiming<S6, Selling,  S6, Selling>(0, v);
}

