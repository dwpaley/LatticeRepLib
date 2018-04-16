// S6Classifier.cpp : Defines the entry point for the console application.
//

#include <algorithm>

#include "C3.h"
#include "GenerateRandomLattice.h"
#include "LRL_ToString.h"
#include "PairReporter.h"
#include "S6.h"
#include "S6Dist.h"
#include "StoreResults.h"


int seed = 1;

unsigned long PositivePosition(const S6& s) {
   if (s.CountPositive() != 1) return 19191;
   unsigned long pos = 0;
   for (unsigned long i = 0; i < 6; ++i) {
      if (s[i] > 0.0) pos = i;
   }
   return pos;
}

C3 SortC3( const C3& c3in) {
   C3 c3(c3in);
   bool again = true;
   while( again) {
      again = false;
      if (abs(c3[0]) > abs(c3[1])) {
         again = true;
         std::complex<double> temp = c3[0];
         c3[0] = c3[1];
         c3[1] = temp;
      }
      if (abs(c3[1]) > abs(c3[2])) {
         again = true;
         std::complex<double> temp = c3[1];
         c3[1] = c3[2];
         c3[2] = temp;
      }
   }
   return c3;
}

unsigned long ClassifyAsymmetricUnit(const C3& c3) {
   const bool b1 = abs(c3[0]) < abs(c3[1]);
   const bool b2 = abs(c3[1]) < abs(c3[2]);
   const bool b3 = c3[0].real() < c3[0].imag();
   const bool b4 = c3[1].real() < c3[1].imag();
   const bool b5 = c3[2].real() < c3[2].imag();
   const unsigned long key = (b1 ? 16 : 0) + (b2 ? 8 : 0) + (b3 ? 4 : 0) + (b4 ? 2 : 0) + (b5 ? 1 : 0);
   return key;
}

C3 ProcessC3(const C3& c3in) {
   C3 c3(SortC3(c3in));
   if (std::abs(c3[0].real()) > std::abs(c3[0].imag())) C3::ComplexInvertSwap(c3[0], c3[1]);
   if (std::abs(c3[1].real()) > std::abs(c3[1].imag())) C3::ComplexInvertSwap(c3[1], c3[2]);
   return c3;
}

int main() {

   StoreResults<unsigned long, std::string> store(10);
   GenerateRandomLattice<C3> generator(seed);

   for (unsigned long i = 0; i < 1000000; ++i) {
      C3 c3 = ProcessC3(generator.randSellingReduced());
      c3 = ProcessC3(c3);
      c3 = ProcessC3(c3);
      c3 = ProcessC3(c3);
      const unsigned long key = ClassifyAsymmetricUnit(c3);
      const std::string str = LRL_ToString("C3", c3, "  S6", S6(c3), "");
      store.Store(key, str);
   }
   store.ShowResultsByKeyAscending();
   return 0;
}

