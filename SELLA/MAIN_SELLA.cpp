// SELLA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "Delone.h"
#include "GenerateRandomLattice.h"
#include "LRL_ToString.h"
#include "S6.h"
#include "Selling.h"
#include "StoreResults.h"

StoreResults<std::string, S6> store(100);

std::vector<unsigned long> FindS6Zeros( const S6& s) {
   std::vector<unsigned long> v;
   for (unsigned long i = 0; i < 6; ++i) if (s[i] == 0) v.push_back(i);
   return v;
}

S6 OneBound(const std::string& label, const S6& s1) {
   static const std::vector< S6(*)(const S6&)> fnRedn = S6::SetReduceFunctions();

   unsigned long nzero = 0;
   for (unsigned long i = 0; i < 6; ++i) if (s1[i] == 0) nzero = i;
   S6 s6temp = fnRedn[nzero](s1);
   store.Store(label, fnRedn[nzero](s1));
   return fnRedn[nzero](s1);
}

std::vector<S6> TwoBounds(const std::string& label, const S6& s1) {
   static const std::vector< S6(*)(const S6&)> fnRedn = S6::SetReduceFunctions();
   std::vector<unsigned long> v = FindS6Zeros(s1);
   std::vector<S6> vs6;
   std::cout << s1 << std::endl;
   std::cout << "v " << v[0] << " " << v[1] << std::endl;
   store.Store(label, fnRedn[v[0]](s1));
   store.Store(label, fnRedn[v[1]](s1));
   //store.Store(label, fnRedn[v[0]](fnRedn[1](s1)));
   //store.Store(label, fnRedn[v[1]](fnRedn[0](s1)));
}

void ThreeBounds(const std::string& label, const S6& s1) {
}

template<typename T>
std::string ListVector( const std::vector<T>& v ) {
   std::string s;
   for (unsigned long i = 0; i < v.size(); ++i) s += "2 " + LRL_ToString(v[i]) + "\n";
   return s;
}


void Expand( const std::string& s, const MatS6& m ) {
   static int seed = 19191;
   GenerateRandomLattice<S6> generate(seed);
   const S6 ran = generate.randSellingReduced();
   const S6 s6 = m * ran;

   switch (s6.CountZeros()) {
   case 0:
      return;
      break;
   case 1:
      std::cout << LRL_ToString(OneBound(s, s6)) << std::endl;
      break;
   case 2:
      std::cout << ListVector(TwoBounds(s, s6));
      break;
   case 3:
      ThreeBounds(s, s6);
      break;
   default:
      throw;
      break;
   }

}


int main()
{
   static const std::vector< std::pair<std::string, MatS6> > vDeloneTypes = Delone::LoadLabeledLatticeTypeProjectors();

   Expand(vDeloneTypes[7].first, vDeloneTypes[7].second);

   for ( unsigned long i=0; i<vDeloneTypes.size(); ++i ) {
      
   
   }
   store.ShowResults();
   const int  i19191 = 19191;
}
