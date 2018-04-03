// ForHJB.cpp : Defines the entry point for the console application.
//

#include <cfloat>
#include <vector>

#include "S6.h"
#include "GenerateRandomLattice.h"
#include "S6Dist.h"


void TestWithinSellingReducedOrthant(const S6& v1, const S6& v2) {
   /*
   This is a test to show that only one of the two search vectors
   needs to have its 24 reflections checked. Both vectors have been 
   chosen so that reflections will find a shorter distance between than
   the simple Euclidean distance. In other words, in some sense they
   are in different asymmetric units within the Selling-reduced 
   orthant. 24 reflections are applied seperately to each and then 
   to both. The latter 3 tests all generate the same minimal 
   distance.
   */
   S6Dist s6dist(1);
   static const std::vector< S6(*)(const S6&)> refl = S6::SetRelectionFunctions();

   const double d1 = (v1 - v2).norm();
   const double d2 = s6dist.MinForListOfS6(v1, S6Dist::Generate24Reflections(v2)).first;
   const double d3 = s6dist.MinForListOfS6(v2, S6Dist::Generate24Reflections(v1)).first;
   const double d4 = s6dist.MinForListOfS6(S6Dist::Generate24Reflections(v1), S6Dist::Generate24Reflections(v2)).first;

   std::cout << "in TestWithinSellingReducedOrthant " << d1 << "       " << d2 << "  " << d3 << "  " << d4 << std::endl;
}

void TestUsingOneUnreduce( const S6& v1, const S6& v2 ) {
/*
This is a test to show that outer (final) application of 24 reflections need
only be applied to v1 or v2. So the 2nd and 3rd printed values should
be the same. If they are not the same as the first value, that is a sign
that DistanceBetween is lacking some reflections.
*/
   S6Dist s6dist(1);
   static const std::vector< S6(*)(const S6&)> refl = S6::SetRelectionFunctions();
   const double d1 = s6dist.DistanceBetween(v1, v2);
   double mind1 = DBL_MAX;
   for (unsigned long i = 0; i<24; ++i) {
      const double testd = s6dist.DistanceBetween(v1, refl[i](v2));
      if (testd < mind1) mind1 = testd;
   }

   double mind2 = DBL_MAX;
   for (unsigned long i = 0; i<24; ++i) {
      const double testd = s6dist.DistanceBetween(refl[i](v1), v2);
      if (testd < mind2) mind2 = testd;
   }

   std::cout << "in TestUsingOneUnreduce, test 2 " << d1 << "      mind1 " << mind1 << "  mind2 " << mind2 << std::endl;
}

int main()
{
   int seed = 1;
   GenerateRandomLattice<S6> generate(seed);
   const S6 v1 = generate.randSellingReduced();
   generate.randSellingReduced();
   const S6 v2 = generate.randSellingReduced();


   TestWithinSellingReducedOrthant(v1, v2);
   TestUsingOneUnreduce(v1, v2);
   return 0;
}

