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

StoreResults<std::string, S6> store(5);

std::vector<unsigned long> FindS6Zeros( const S6& s) {
   std::vector<unsigned long> v;
   for (unsigned long i = 0; i < 6; ++i) if (s[i] == 0) v.push_back(i);
   return v;
}

void OneBound(const std::string& label, const S6& s1) {
   static const std::vector< S6(*)(const S6&)> fnRedn = S6::SetReduceFunctions();

   store.Store(label, s1);
   unsigned long nzero = 0;
   for (unsigned long i = 0; i < 6; ++i) if (s1[i] == 0) nzero = i;
   S6 s6temp = fnRedn[nzero](s1);
   if ( s6temp != s1 ) store.Store(label, fnRedn[nzero](s1));
}

std::vector<S6> CleanVector( const std::vector<S6>& v1 ) {
   std::vector<S6> vout;
   if ( !vout.empty() ) {
      vout[0] = v1[0];
      for ( unsigned long i=1; i<v1.size(); ++i ) {
         if (v1.end() != std::find(vout.begin(), vout.end(), v1[i])) vout.push_back(v1[i]);
      }
   }

   return vout;
}

void TwoBounds(const std::string& label, const S6& s1) {
   store.Store(label, s1);
   static const std::vector< S6(*)(const S6&)> fnRedn = S6::SetReduceFunctions();
   std::vector<unsigned long> v = FindS6Zeros(s1);
   const S6 a = fnRedn[v[0]](s1);
   const S6 b = fnRedn[v[1]](s1);
   store.Store(label, a);
   store.Store(label, b);
   store.Store(label, fnRedn[v[0]](b));
   store.Store(label, fnRedn[v[1]](a));
}

void ThreeBounds(const std::string& label, const S6& s1) {
   store.Store(label, s1);
   static const std::vector< S6(*)(const S6&)> fnRedn = S6::SetReduceFunctions();
   std::vector<unsigned long> v = FindS6Zeros(s1);
   const S6 a = fnRedn[v[0]](s1);
   const S6 b = fnRedn[v[1]](s1);
   const S6 c = fnRedn[v[2]](s1);
   store.Store(label, a);
   store.Store(label, b);
   store.Store(label, c);
   //store.Store(label, fnRedn[v[0]](b));
   //store.Store(label, fnRedn[v[1]](a));
}

template<typename T>
std::string ListVector( const std::vector<T>& v ) {
   std::string s;
   for (unsigned long i = 0; i < v.size(); ++i) s += "2 " + LRL_ToString(v[i]) + "\n";
   return s;
}

static int seed = 19191;

std::vector<S6> MakeSampleType(const std::string& s, const MatS6& m) {
   GenerateRandomLattice<S6> generate(seed);
   bool valid = false;
   S6 s6;
   s6.SetValid(false);
   int count = 0;
   bool again = true;

   while (again && count < 10) {
      const S6 ran = generate.randSellingReduced();
      s6 = m * ran;
      again = !s6.GetValid();
      ++count;
   }
   std::vector<S6> v;
   if (!again) v.push_back(s6);
   return v;
}

void Expand(const std::string& s, const MatS6& m) {
   const std::vector<S6> v = MakeSampleType(s, m);

   bool b = v[0].IsValid();

   if (!v.empty() && v[0].IsValid()) {
      const S6 s6 = v[0];
      switch (s6.CountZeros()) {
      case 0:
         return;
         break;
      case 1:
         OneBound(s, s6);
         break;
      case 2:
         TwoBounds(s, s6);
         break;
      case 3:
         ThreeBounds(s, s6);
         break;
      default:
         throw;
         break;
      }
   }

}


int main()
{
   static const std::vector< std::pair<std::string, MatS6> > vDeloneTypes = Delone::LoadLabeledLatticeTypeProjectors();


   for ( unsigned long i=0; i<vDeloneTypes.size(); ++i ) {
      
      Expand(vDeloneTypes[i].first, vDeloneTypes[i].second);

   }
   store.ShowResults();
   const int  i19191 = 19191;
}
