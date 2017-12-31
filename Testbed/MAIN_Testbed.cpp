// Testbed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "B4.h"
#include "D7.h"
#include "G6.h"
#include "D7Dist_.hpp"
#include "LRL_Cell.h"
#include "LRL_StringTools.h"
#include "LRL_ToString.h"
#include "LRL_MaximaTools.h"
#include "Niggli.h"
#include "S6.h"
#include "S6Dist.h"
#include "Selling.h"
#include "LRL_Vector3.h"


//void TransformAndTestVector( const D7& testvec, const D7_Subboundary& sb ) {
//   const D7 transformedRandom = sb.GetTransform( ) * testvec;
//   const std::pair<int, std::string> id = D7_IdentifyNearbyBoundaries( transformedRandom, 10 );
//   boundarymap[sb.GetName( )] = std::make_pair( sb.GetName( ) + " transforms to  " + id.second, "" );
//}

template<typename T>
void TestToType() {
   T a, b;
   if (a.size() == 6) {
      a = T("10 11 12 90 90 90");          // from string
      b = T(G6("10 10 10  10 10 10 "));     // from G6
   }
   else if (a.size() == 7)
   {
      a = T("10 11 12 13 14 15 16");          // from string
      b = T("10 10 10  60 30 30 30 ");     // from G6
   }
   else if (a.size() == 4)
   {
      a = T(LRL_Cell("10 11 12 90 90 90"));
      b = T(G6("10 10 10  10 10 10 "));
   }
   else
   {
      throw;
   }
   D7 d7(b);
   T c(d7);                           // from D7
   T d(c);                            // from LRL_Cell
   S6 ds("5 5 5 -20 -20 -20");
   T e(ds);                           // from DeloneScalars (D6)
   B4 dt(G6("10 10 10  10 10 10 "));
   T f(dt);

   std::cout << a << std::endl;
   std::cout << b << std::endl;
   std::cout << c << std::endl;
   std::cout << d << std::endl;
   std::cout << e << std::endl;
   std::cout << f << std::endl;

   std::cout << std::endl;

   std::cout << LRL_ToString(a) << std::endl;
   std::cout << LRL_ToString(b) << std::endl;
   std::cout << LRL_ToString(c) << std::endl;
   std::cout << LRL_ToString(d) << std::endl;
   std::cout << LRL_ToString(e) << std::endl;
   std::cout << LRL_ToString(f) << std::endl;

}


int Negatives(const S6& s) {
   int n = 0;
   for (int i = 0; i < 6; ++i) n += (s[i] <= 0.0) ? 1 : 0;
   return n;
}

static const double pi = 4.0*atan(1.0);

bool BadTetrahedron(const S6& s6) {
   B4 b4(s6);
   const double angle_ad = Vector_3::Angle(b4[0], Vector_3::GetZeroVector(), b4[1]);
   const double angle_bd = Vector_3::Angle(b4[0], Vector_3::GetZeroVector(), b4[2]);
   const double angle_cd = Vector_3::Angle(b4[0], Vector_3::GetZeroVector(), b4[3]);

   if (angle_ad < 0.01) return true;
   if (angle_bd < 0.01) return true;
   if (angle_cd < 0.01) return true;
   if (angle_ad > 0.999*pi) return true;
   if (angle_bd > 0.999*pi) return true;
   if (angle_cd > 0.999*pi) return true;
   return false;
}

std::string Signature(const int negatives, const S6& s6) {
   std::string s = LRL_ToString(negatives) + "_";
   for (unsigned long i = 0; i < 6; ++i) {
      s.push_back((s6[i] <= 0.0) ? '-' : '+');
      if (i == 2) s.push_back(',');
   }
   return s;
}

StoreResults<std::string, S6> g_storeRand(100);
StoreResults<int, LRL_Cell> g_store(100);
StoreResults<std::string, LRL_Cell> g_storeStr(100);
StoreResults<std::string, std::string> g_storeStrStr(100);

void Reflects() {
   std::vector<MatD7> refl;
   MatD7 ref;
   for (unsigned long i = 0; i < 24; ++i) {
      for (unsigned long k = 0; k < 49; ++k) {
         ref[k] = D7Refl[i][k];
      }
      refl.push_back(ref);
   }
   for (unsigned long i = 0; i < 10000000; ++i) {  // 100000000
      S6 s6(100.0*S6::rand());
      int n = Negatives(s6);
      LRL_Cell cell(s6);
      int invalids = 0;
      for (int k = 0; k < 6; ++k) {
         invalids += (cell[k] < 1.0E20) ? 0 : 1; // testing for invalid FP number
      }

      for (int k = 3; k < 6; ++k) {
         if (cell[k] < 0.01) ++invalids; // zero degree angle
         if (cell[k] > 0.999*pi) ++invalids;  // 180 degree angle
      }

      if (cell[3] + cell[4] + cell[5] > 2.0*pi) ++invalids; // cell angles sum to more than 360 degrees
      if (invalids == 0 && BadTetrahedron(s6)) ++invalids;
      const std::string signature = Signature(n, s6);
      if (invalids == 0) {
         g_storeRand.Store(Signature(n, s6), s6);
         S6 s6red;
         Selling::Reduce(s6, s6red);
         g_storeStrStr.Store(signature, LRL_ToString(s6) + "   " + LRL_ToString(s6red));
      }
      if (!g_storeStr.HasKey(signature) && invalids == 0) {
         for (unsigned long kkkk = 0; kkkk < 24; ++kkkk) {
            //g_store.Store(n, refl[kkkk]*cell);
            g_storeStr.Store(signature, refl[kkkk] * cell);
         }
      }
   }

   g_store.ShowResultsByKey();
   g_storeStrStr.ShowResultsByKey();
   exit(0);
   std::cout << g_storeStr.Herald() << std::endl;
   std::vector < std::string > keys = g_storeStr.GetKeys();

   for (int i = 0; i < keys.size(); ++i) {
      const std::vector<std::pair<std::string, LRL_Cell> > v = g_storeStr.FindResult(keys[i]);
      /*if (v.size() > 0) */std::cout << "key " << keys[i] << "    samples = " << v.size() << "   count  " << g_storeStr.GetItemCount(keys[i]) << std::endl;
      for (int k = 0; k < v.size(); ++k) {
         std::cout << v[k].second.CellWithDegrees() << "    " << S6(v[k].second) << std::endl;
      }
      std::cout << std::endl;
   }
   g_storeRand.ShowResultsByKey();
}

void TestUnreducePairs() {
   // tests to show that the reduce and unreduce pairs plus the 24 reflections generate the same set of cells

   const S6 s6(LRL_Cell::randDeloneReduced());
   S6Dist s6dist(DBL_MAX);

   static std::vector< std::pair<S6(*)(const S6&), S6(*)(const S6&)> > unreducers = S6Dist::SetUnreduceFunctionPairs();

   std::vector<S6> vinside;
   std::vector<S6> voutside;

   for (unsigned long i = 0; i < unreducers.size(); ++i) {
      vinside.push_back(unreducers[i].first(s6));  // generate using the first of each unreduce pair of functions
      voutside.push_back(unreducers[i].second(s6));  // generate using the second of each unreduce pair of functions
   }

   //   voutside = s6dist.Generate24Reflections(voutside); // for outside, generate the 24 reflections for each unreduced cell

   std::cout << "vinside   " << vinside.size() << std::endl;
   for (unsigned long i = 0; i < vinside.size(); ++i) {
      std::cout << vinside[i] << std::endl;
   }
   std::cout << std::endl;

   std::cout << "voutside   " << voutside.size() << std::endl;
   for (unsigned long i = 0; i < voutside.size(); ++i) {
      std::cout << voutside[i] << std::endl;
   }
   std::cout << std::endl;

   std::cout << "vinside   Cell, unreduced angles in degrees       " << vinside.size() << std::endl;
   for (unsigned long i = 0; i < vinside.size(); ++i) {
      std::cout << LRL_Cell(vinside[i]).CellWithDegrees() << std::endl;
   }
   std::cout << std::endl;

   std::cout << "vinside   NIGGLI REDUCED --  G6        " << vinside.size() << std::endl;
   for (unsigned long i = 0; i < vinside.size(); ++i) {
      S6 s6out;
      Niggli::Reduce<S6>((vinside[i]), s6out);
      std::cout << G6(s6out) << std::endl;
   }
   std::cout << std::endl;

   const CNearTree<S6> tree = voutside;

   for (unsigned long i = 0; i < vinside.size(); ++i) {
      CNearTree<S6>::iterator it = tree.NearestNeighbor(0.0001, vinside[i]);
      std::cout << i << "  " << ((it == tree.end()) ? "bad" : "good ") << std::endl;
   }
   exit(0);
}

void TestSellingReduceUnreduceFunctions() {
   // test of functions for Selling reduce/unreduce
   //std::vector< std::pair<S6(*)(const S6&), S6(*)(const S6&)> > vf =S6Dist::SetUnreduceFunctionPairs();
   //S6 temp;
   //temp[0] = 1;
   //temp[1] = 3;
   //temp[2] = 5;
   //temp[3] = 7;
   //temp[4] = 11;
   //temp[5] = 13;
   //std::cout <<  vf[0].first(temp) << std::endl;;
   //std::cout <<  vf[0].second(temp) << std::endl;

   //exit(0);

   //const std::vector<std::pair<MatS6, MatS6> > vRed = S6Dist::SetunreductionReductionMatricesFromReductionMatrices();
   //for (unsigned long i = 0; i < vRed.size(); ++i) {
   //   std::cout << "For scale " << i << "1" << std::endl;
   //   std::cout << MaximaTools::MaximaFromMat(vRed[i].first) << std::endl << std::endl;
   //   std::cout << "For scale " << i << "2" << std::endl;
   //   std::cout << MaximaTools::MaximaFromMat(vRed[i].second) << std::endl << std::endl;
   //}
   //exit(0);
   //std::list<S6> vs6;
   //for (unsigned long i = 0; i < 5000000; ++i) {
   //   Cell cl = Cell::rand();
   //   vs6.push_back(S6(cl));;
   //}
}

void TestReductionTiming() {
   //std::list<S6>::iterator it;

   //S6 red2;
   //std::cout << CreateFileName::Create("", "") << std::endl;;
   //unsigned long trials1 = vs6.size()/100;
   //std::cout << trials1 << std::endl;
   //for (it = vs6.begin(); it != vs6.end(); ++it) {
   //   S6 red1 = Delone::Reduce(*it);
   //}
   //std::cout << CreateFileName::Create("", "") << std::endl;;

   //unsigned long trials2 = vs6.size();
   //std::cout << trials2 << std::endl;
   //for (it = vs6.begin(); it != vs6.end(); ++it) {
   //   Delone::ReduceUnsortedByFunction(*it, red2);
   //}
   //std::cout << CreateFileName::Create("", "") << std::endl;;
   //exit(0);

}

void TestConversions() {
   //-------------------------------------------------------------------------------------------
   LRL_Cell c;
   c[0];
   std::cout << LRL_Cell::GetName() << std::endl;
   TestToType<LRL_Cell>();

   std::cout << std::endl << std::endl;
   std::cout << G6::GetName() << std::endl;
   TestToType<G6>();

   std::cout << std::endl << std::endl;
   std::cout << D7::GetName() << std::endl;
   TestToType<D7>();

   std::cout << std::endl << std::endl;
   std::cout << S6::GetName() << std::endl;
   TestToType<S6>();

   std::cout << std::endl << std::endl;
   std::cout << B4::GetName() << std::endl;
   TestToType<B4>();
}

void CompareBothUnreduces() {
   // tests to show that the reduce and unreduce pairs plus the 24 reflections generate the same set of cells

   const S6 s6(LRL_Cell::randDeloneReduced());
   std::cout << " initial REDUCED input  " << LRL_MaximaTools::MaximaFromString(LRL_ToString(s6)) << std::endl;
   S6Dist s6dist(DBL_MAX);

   // get the functions that do the pairs of unreduces
   static std::vector< std::pair<S6(*)(const S6&), S6(*)(const S6&)> > unreducers = S6Dist::SetUnreduceFunctionPairs();

   std::vector<S6> vinside;
   std::vector<S6> voutside;

   // unreduce by each of the 6 unreduces of the two types
   for (unsigned long i = 0; i < unreducers.size(); ++i) {
      vinside.push_back(unreducers[i].first(s6));  // generate using the first of each unreduce pair of functions
      voutside.push_back(unreducers[i].second(s6));  // generate using the second of each unreduce pair of functions
   }

   // for outside, generate the 24 reflections for each unreduced cell
   //voutside = s6dist.Generate24Reflections(voutside); 

   std::cout << "vinside   " << vinside.size() << std::endl;
   for (unsigned long i = 0; i < vinside.size(); ++i) {
      std::cout << LRL_MaximaTools::MaximaFromString(LRL_ToString(vinside[i])) << std::endl;
   }
   std::cout << std::endl;

   std::cout << "voutside   " << voutside.size() << std::endl;
   for (unsigned long i = 0; i < voutside.size(); ++i) {
      std::cout << LRL_MaximaTools::MaximaFromString(LRL_ToString(voutside[i])) << std::endl;
   }
   std::cout << std::endl;


   const CNearTree<S6> tree = voutside;

   // put a bad one in
   vinside.push_back(1.0001 * vinside[0]);

   // see if every one of the insides is in outside
   // this can never be true for the different unreduce targets, so we get
   // no spurious results
   // MAKE SURE THAT THE LAST ONE IS BAD !!!!!
   for (unsigned long i = 0; i < vinside.size(); ++i) {
      CNearTree<S6>::iterator it = tree.NearestNeighbor(0.0001, vinside[i]);
      std::cout << i << "  " << ((it == tree.end()) ? "bad" : "good ") << std::endl;
   }
   exit(0);
}

int main(int argc, char *argv[])
{
   //std::cout << LRL_ToString(S6("1 2 3 4 5 6")) << std::endl;
   //std::cout << LRL_ToString(G6("1 2 3 4 5 6")) << std::endl;
   //std::cout << LRL_ToString(D7("1 2 3 4 5 6 7")) << std::endl;
   //std::cout << LRL_ToString(LRL_Cell("10 20 40 60 70 80")) << std::endl;
   //std::cout << LRL_ToString(Vector_3(1,2,3)) << std::endl;

   //std::cout << "MatB4" << std::endl << LRL_ToString(MatB4("1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6")) << std::endl;
   //std::cout << "MatS6" << std::endl << LRL_ToString(MatS6()) << std::endl;
   //std::cout << "MatG6" << std::endl << LRL_ToString(MatG6()) << std::endl;
   //std::cout << "MatD7" << std::endl << LRL_ToString(MatD7()) << std::endl;

   std::cout << "main file name *** " << __FILE__ << " ***" << std::endl;

   CompareBothUnreduces();
   //TestUnreducePairs();
   exit(0);

   //Selling::SetDebug(true);

   //TestConversions();

   LRL_Cell c1("10 20 40 60 70 80");
   S6 s1(c1);
   Reflects();
   exit(0);
   return 0;
}

