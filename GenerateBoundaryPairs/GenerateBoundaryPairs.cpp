// GenerateBoundaryPairs.cpp : Defines the entry point for the console application.
//

#include <algorithm>
#include <cfloat>
#include <iomanip>
#include <iostream>
#include <utility>

#include "GenerateRandomLattice.h"
#include "LRL_Cell_Degrees.h"
#include "LRL_ToString.h"
#include "PairReporter.h"
#include "S6.h"
#include "StoreResults.h"


static std::pair<S6, S6> BinarySearchReduced(const S6& s1, const S6& s2, const int npass) {
   const double deltanorm = (s1 - s2).norm();
   if (npass <= 0 || deltanorm < 0.01) {
      const double n1 = s1.norm();
      const double n2 = s2.norm();
      //std::cout << "npass " << npass << "  deltanorm " << deltanorm << std::endl;
      return std::make_pair(s1 / deltanorm, s2 / deltanorm);
   }
   // norm doesn't work here because s2 is invalid !!!!!!!!!!
   // operator- doesn't work here because s2 is invalid !!!!!!!!!!
   S6 s6delta;
   for (unsigned long i = 0; i < 6; ++i) s6delta[i] = s2[i] - s1[i];
   S6 midpoint = s1 + 0.5 * s6delta;
   const bool bmid = LRL_Cell(midpoint).GetValid();
   midpoint.SetValid(bmid);

   const bool isReduced = midpoint.IsAllMinus();

   if (isReduced) {
      return BinarySearchReduced(midpoint, s2, npass - 1);
   }
   else {
      return BinarySearchReduced(s1, midpoint, npass - 1);
   }
}

static int seed = 2;

static std::pair<S6, S6> GeneratePair_Reduced_Unreduced( const unsigned long numberOfZeros) {
   static const std::vector< S6(*)(const S6&)> refl = S6::SetRelectionFunctions();
   static GenerateRandomLattice<S6> generator(seed);
   const S6 v1 = generator.randSellingReduced();
   const S6 v2 = generator.GenerateExtreme();

   const std::pair<S6, S6> output = BinarySearchReduced(v1, v2, 12);
   //std::cout << std::endl;
   //std::cout << "cell 1 " << LRL_Cell_Degrees(output.first) << std::endl;
   //std::cout << "cell 2 " << LRL_Cell_Degrees(output.second) << std::endl;
   //std::cout << "S6 1" << output.first << std::endl;
   //std::cout << "S6 2" << output.second << std::endl;
   S6 out;
   const bool b = Selling::Reduce(output.second, out);
   //std::cout << "reduced  2   " << out << std::endl;
   //std::cout << "G6   1   " << G6(output.first) << std::endl;
   //std::cout << "G6   2   " << G6(output.first) << std::endl;
   //std::cout << "G6 reduced  2   " << G6(output.second) << std::endl;
   //std::cout << "cell reduced  2   " << LRL_Cell_Degrees(output.second) << std::endl;
   //std::cout << "#1 to #2 " << std::fixed << std::setprecision(3) << (output.first - output.second).norm() << "  #1 to reduced #2 " << (output.first - out).norm() << std::endl << std::endl;
   const int random = rand() & 23;
   return std::make_pair(output.first,refl[random](out));
}

int Rank( const S6& s ) {
   const double length = s.norm();
   double minS6 = DBL_MAX;;

   unsigned long nzero = 0;
   for ( unsigned long i=0; i<6; ++i ) {
      minS6 = std::abs(std::min(minS6,s[i]));
   }
   return log10(minS6);
}

int main()
{
   StoreResults<int, std::string > store(5);
   PairReporter<S6, S6> output;

   for (unsigned long i = 0; i < 1000; ++i) {
      output = GeneratePair_Reduced_Unreduced(0);
      output.SetSeparator("     ");
      const int rank = Rank(output.GetFirst());
      store.Store(rank, LRL_ToString( "S", output.GetFirst(), "\nS    ", output.GetSecond(), "\n"));
   }

   store.ShowResults();
   return 0;
}


/*
K1 (cI)
1 1 1  1 1 1
1 1 1  1 1 1
1 1 1  1 1 1
1 1 1  1 1 1
1 1 1  1 1 1
1 1 1  1 1 1

K3(cF)
1 1 0  1 1 0
1 1 0  1 1 0
0 0 0  0 0 0
1 1 0  1 1 0
1 1 0  1 1 0
0 0 0  0 0 0

K5 (cP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  1 1 1
0 0 0  1 1 1
0 0 0  1 1 1

Q1 (tI)
1 1 0  1 1 0
1 1 0  1 1 0
0 0 1  0 0 1
1 1 0  1 1 0
1 1 0  1 1 0
0 0 1  0 0 1


Q2 (tI)
1 1 0  1 1 0
1 1 0  1 1 0
0 0 0  0 0 0
1 1 0  1 1 0
1 1 0  1 1 0
0 0 0  0 0 1

Q5 (tP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  1 1 0
0 0 0  1 1 0
0 0 0  0 0 1

R1 (rP)
1 1 1  0 0 0
1 1 1  0 0 0
1 1 1  0 0 0
0 0 0  1 1 1
0 0 0  1 1 1
0 0 0  1 1 1

R3 (rP)
1 0 1  0 1 0
0 0 0  0 0 0
1 0 1  0 1 0
0 0 0  1 0 0
1 0 1  0 1 0
0 0 0  0 0 0

O1A (oF)
1 1 0  1 1 0
1 1 0  1 1 0
0 0 1  0 0 0
1 1 0  1 1 0
1 1 0  1 1 0
0 0 0  0 0 1

O1B (oI)
1 1 0  1 1 0
1 1 0  1 1 0
0 0 1  0 0 1
1 1 0  1 1 0
1 1 0  1 1 0
0 0 1  0 0 1

O2 (oI)
1 0 0  0 1 0
0 1 0  1 0 0
0 0 0  0 0 0
0 1 0  1 0 0
1 0 0  0 1 0
0 0 0  0 0 0

O3 (oI)
1 0 0  0 1 0
0 1 0  1 0 0
0 0 0  0 0 0
1 0 0  0 1 0
0 1 0  1 0 0
0 0 0  0 0 0

O4 (oP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 1  0 0 0
0 0 0  1 1 0
0 0 0  1 1 0
0 0 0  0 0 1

O5 (oP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  0 0 0
0 0 0  1 0 0
0 0 0  0 1 0
0 0 0  0 010

M1A (mC)
1 1 0  0 0 0
1 1 0  0 0 0
0 0 1  0 0 0
0 0 0  1 1 0
0 0 0  1 1 0
0 0 0  0 0 1

M1B (mC)
1 0 0  1 0 0
0 1 0  0 1 0
0 0 1  0 0 0
1 0 0  1 0 0
0 1 0  0 1 0
0 0 0  0 0 1

M2A (mC)
1 0 0  1 0 0
0 1 0  0 1 0
0 0 0  0 0 0
1 0 0  1 0 0
0 1 0  0 1 0
0 0 0  0 0 1

M1B (mC)
1 0 0  1 0 0
0 1 0  0 1 0
0 0 0  0 0 0
0 1 0  0 1 0
0 0 0  0 1 0
0 0 0  0 0 1

M2B (mC)
1 0 0  0 0 0
0 1 0  1 0 0
0 0 0  0 0 0
0 1 0  1 0 0
0 0 0  0 1 0
0 0 0  0 0 1

M3 (mC)
1 0 0  0 0 0
0 1 0  0 1 0
0 0 0  0 0 0
0 0 0  1 0 0
0 1 0  0 1 0
0 0 0  0 0 0

M4 (mP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 1  0 0 0
0 0 0  1 0 0
0 0 0  0 1 0
0 0 0  0 0 1

T1 (aP)
1 0 0  0 0 0
0 1 0  0 0 0
0 0 1  0 0 0
0 0 0  1 0 0
0 0 0  0 1 0
0 0 0  0 0 1

T2 (aP)
1 0 0  0 0 0
0 1 0  0 0 0
0 0 0  0 0 0
0 0 0  1 0 0
0 0 0  0 1 0
0 0 0  0 0 1

T3 (aP)
1 0 0  0 0 0
0 1 0  0 0 0
0 0 0  0 0 0
0 0 0  1 0 0
0 0 0  0 1 0
0 0 0  0 0 0

H4 (hP)
0 0 0  0 0 0
0 0 0  0 0 0
0 0 1  1 1 0
0 0 1  1 1 0
0 0 1  1 1 0
0 0 0  0 0 1

vDeloneTypes.push_back(MatS6( "1 1 1 1 1 1  1 1 1 1 1 1  1 1 1 1 1 1  1 1 1 1 1 1  1 1 1 1 1 1  1 1 1 1 1 1" ));  //    K1 (cI)
vDeloneTypes.push_back(MatS6( "1 1 0 1 1 0  1 1 0 1 1 0  0 0 0 0 0 0  1 1 0 1 1 0  1 1 0 1 1 0  0 0 0 0 0 0" ));  //    K3 (cF)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 1 1 1  0 0 0 1 1 1  0 0 0 1 1 1" ));  //    K5 (cP)
vDeloneTypes.push_back(MatS6( "1 1 0 1 1 0  1 1 0 1 1 0  0 0 1 0 0 1  1 1 0 1 1 0  1 1 0 1 1 0  0 0 1 0 0 1" ));  //    Q1 (tI)
vDeloneTypes.push_back(MatS6( "1 1 0 1 1 0  1 1 0 1 1 0  0 0 0 0 0 0  1 1 0 1 1 0  1 1 0 1 1 0  0 0 0 0 0 1" ));  //    Q2 (tI)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 1 1 0  0 0 0 1 1 0  0 0 0 0 0 1" ));  //    Q5 (tP)
vDeloneTypes.push_back(MatS6( "1 1 1 0 0 0  1 1 1 0 0 0  1 1 1 0 0 0  0 0 0 1 1 1  0 0 0 1 1 1  0 0 0 1 1 1" ));  //    R1 (rP)
vDeloneTypes.push_back(MatS6( "1 0 1 0 1 0  0 0 0 0 0 0  1 0 1 0 1 0  0 0 0 1 0 0  1 0 1 0 1 0  0 0 0 0 0 0" ));  //    R3 (rP)
vDeloneTypes.push_back(MatS6( "1 1 0 1 1 0  1 1 0 1 1 0  0 0 1 0 0 0  1 1 0 1 1 0  1 1 0 1 1 0  0 0 0 0 0 1" ));  //    O1A (oF)
vDeloneTypes.push_back(MatS6( "1 1 0 1 1 0  1 1 0 1 1 0  0 0 1 0 0 1  1 1 0 1 1 0  1 1 0 1 1 0  0 0 1 0 0 1" ));  //    O1B (oI)
vDeloneTypes.push_back(MatS6( "1 0 0 0 1 0  0 1 0 1 0 0  0 0 0 0 0 0  0 1 0 1 0 0  1 0 0 0 1 0  0 0 0 0 0 0" ));  //    O2 (oI)
vDeloneTypes.push_back(MatS6( "1 0 0 0 1 0  0 1 0 1 0 0  0 0 0 0 0 0  1 0 0 0 1 0  0 1 0 1 0 0  0 0 0 0 0 0" ));  //    O3 (oI)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 1 0 0 0  0 0 0 1 1 0  0 0 0 1 1 0  0 0 0 0 0 1" ));  //    O4 (oP)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 0 0 0  0 0 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 1" ));  //    O5 (oP)
vDeloneTypes.push_back(MatS6( "1 1 0 0 0 0  1 1 0 0 0 0  0 0 1 0 0 0  0 0 0 1 1 0  0 0 0 1 1 0  0 0 0 0 0 1" ));  //    M1A (mC)
vDeloneTypes.push_back(MatS6( "1 0 0 1 0 0  0 1 0 0 1 0  0 0 1 0 0 0  1 0 0 1 0 0  0 1 0 0 1 0  0 0 0 0 0 1" ));  //    M1B (mC)
vDeloneTypes.push_back(MatS6( "1 0 0 1 0 0  0 1 0 0 1 0  0 0 0 0 0 0  1 0 0 1 0 0  0 1 0 0 1 0  0 0 0 0 0 1" ));  //    M2A (mC)
vDeloneTypes.push_back(MatS6( "1 0 0 0 0 0  0 1 0 1 0 0  0 0 0 0 0 0  0 1 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 1" ));  //    M2B (mC)
vDeloneTypes.push_back(MatS6( "1 0 0 0 0 0  0 1 0 0 1 0  0 0 0 0 0 0  0 0 0 1 0 0  0 1 0 0 1 0  0 0 0 0 0 0" ));  //    M3 (mC)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 1 0 0 0  0 0 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 1" ));  //    M4 (mP)
vDeloneTypes.push_back(MatS6( "1 0 0 0 0 0  0 1 0 0 0 0  0 0 1 0 0 0  0 0 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 1" ));  //    T1 (aP)
vDeloneTypes.push_back(MatS6( "1 0 0 0 0 0  0 1 0 0 0 0  0 0 0 0 0 0  0 0 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 1" ));  //    T2 (aP)
vDeloneTypes.push_back(MatS6( "1 0 0 0 0 0  0 1 0 0 0 0  0 0 0 0 0 0  0 0 0 1 0 0  0 0 0 0 1 0  0 0 0 0 0 0" ));  //    T3 (aP)
vDeloneTypes.push_back(MatS6( "0 0 0 0 0 0  0 0 0 0 0 0  0 0 1 1 1 0  0 0 1 1 1 0  0 0 1 1 1 0  0 0 0 0 0 1" ));  //    H4 (hP)



*/
