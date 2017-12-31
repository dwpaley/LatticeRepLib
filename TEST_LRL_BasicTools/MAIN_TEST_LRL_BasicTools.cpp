// TEST_LRL_BasicTools.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include"MatN.h"
#include "LRL_MaximaTools.h"
#include "LRL_MinMaxTools.h"
#include "LRL_RandTools.h"
#include "LRL_StringTools.h"
#include "MatN.h"
#include "LRL_RandTools.h" 
#include "StoreResults.h"
#include "VecN.h"

#include "TNear.h"



int main()
{
   StoreResults<int, MatN> sm(5);
   StoreResults<int, VecN> sv(5);
   StoreResults<int, int> si(2);
   StoreResults<double, double> sr(3);
   int seed1 = 0;
   int seed2 = 19191;
   for (unsigned long i = 0; i < 100000; ++i) {
      //si.Store(i/4, i);
      sr.Store(int(20.0+10.0*randfg(seed1)), int(10.0*randfg(seed2)));
   }
   si.ShowResultsByKey();

   sr.ShowResultsByKey();

   std::cout << LRL_ToString(MatN(9)) << std::endl;

   CNearTree<int> nt;
   return 0;
}

