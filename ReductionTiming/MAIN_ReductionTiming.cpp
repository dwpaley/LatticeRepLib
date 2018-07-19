// ReductionTiming.cpp : Defines the entry point for the console application.
//

#include <ctime>
#include <vector>

#include "CellInputData.h"
#include "LRL_Cell.h"
#include "S6.h"
#include "G6.h"
#include "D7.h"
#include "B4.h"
#include "GenerateRandomLattice.h"
#include "MatG6.h"
#include "LRL_ReadLatticeData.h"
#include "LatticeConverter.h"
#include "LRL_ToString.h"
#include "Niggli.h"
#include "Selling.h"
#include "StoreResults.h"

#include "CS6Dist.h"
#include "D7Dist.h"
#include "NCDist.h"
#include "S6Dist.h"
#include "V7Dist.h"

int seed = 19191;

std::vector<CellInputData> ReadAllLatticeData() {
   std::vector<CellInputData> celldata;
   std::string lattice("");
   LRL_ReadLatticeData rcd(seed);
   while (lattice != "EOF") {
      rcd.read();
      lattice = "EOF";
      lattice = rcd.GetLattice();
      if (lattice != "EOF" && !lattice.empty()) {
         rcd.SetVarietyRange(std::make_pair(0, 23));
         celldata.push_back(rcd);
      }
   }
   return celldata;
}

void TestSellingTiming(const std::vector<S6>& testData) {

   for (unsigned long i = 0; i < testData.size(); ++i) {
      S6 s6out;
      Selling::Reduce(testData[i], s6out);
   }
}

void TestNiggliTiming(const std::vector<G6>& testData, const bool doSelling) {
   for (unsigned long i = 0; i < testData.size(); ++i) {
      G6 g6out;
      Niggli::Reduce(testData[i], g6out, doSelling);
   }
}

void TestCS6DistancesTiming(const std::vector<S6>& testData) {
   const unsigned long ntests = testData.size();
   int count = 0;
   const double distA = CS6Dist(testData[0].data(), testData[ntests - 1].data());
   for (unsigned long i = 0; i < ntests - 1; ++i) {
      const double dist = CS6Dist(testData[i].data(), testData[i + 1].data());
   }
}

void TestD7DistancesTiming(const std::vector<S6>& testData) {
   const unsigned long ntests = testData.size();
   int count = 0;
   const double distA = D7Dist(testData[0].data(), testData[ntests - 1].data());
   for (unsigned long i = 0; i < ntests - 1; ++i) {
      const double dist = D7Dist(testData[i].data(), testData[i + 1].data());
   }
}

void TestS6DistancesTiming(const std::vector<S6>& testData) {
   const unsigned long ntests = testData.size();
   int count = 0;
   S6Dist s6dist(1);
   const double distA = s6dist.DistanceBetween(testData[0], testData[ntests - 1]);
   for (unsigned long i = 0; i < ntests - 1; ++i) {
      const double dist = s6dist.DistanceBetween(testData[i], testData[i + 1]);
   }
}

void TestG6DistancesTiming(const std::vector<G6>& testData) {
   const unsigned long ntests = testData.size();
   int count = 0;
   const double distA = NCDist(testData[0].data(), testData[ntests - 1].data());
   for (unsigned long i = 0; i < ntests - 1; ++i) {
      NCDist(testData[i].data(), testData[i + 1].data());
   }
}

void TestV7DistancesTiming(const std::vector<G6>& testData) {
   const unsigned long ntests = testData.size();
   int count = 0;
   const double distA = V7Dist(testData[0].data(), testData[ntests - 1].data());
   for (unsigned long i = 0; i < ntests - 1; ++i) {
      V7Dist(testData[i].data(), testData[i + 1].data());
   }
}

void CheckReduceAndDistanceTiming(const std::vector<S6>& cells) {
   std::cout << cells.size() << std::endl;

   const unsigned long nReduceSamples = cells.size();
   const std::vector<S6> unreducedTestDataS6 = cells;
   std::vector<G6> unreducedTestDataG6;
   for (unsigned long i = 0; i < nReduceSamples; ++i) unreducedTestDataG6.push_back(G6(unreducedTestDataS6[i]));

   StoreResults < std::string, double> store(100);

   auto start = std::clock();

   for (unsigned long cycle = 0; cycle < 10; ++cycle) {
      //---------------------------------- test unreduced reductions
      {
         start = std::clock();
         //std::cout << "Selling " << std::endl;
         TestSellingTiming(unreducedTestDataS6);
         store.Store("Input Selling", std::clock() - start);
         //std::cout << std::clock() - start << " msec" << std::endl;

         start = std::clock();
         //std::cout << "Niggli, preSelling" << std::endl;
         TestNiggliTiming(unreducedTestDataG6, true);
         store.Store("Niggli, preSelling", std::clock() - start);
         //std::cout << std::clock() - start << " msec" << std::endl;

         start = std::clock();
         //std::cout << "only Niggli" << std::endl;
         TestNiggliTiming(unreducedTestDataG6, false);
         store.Store("Only Niggli", std::clock() - start);
         //std::cout << std::clock() - start << " msec" << std::endl;
      }
   }
   store.ShowResults();
   std::cout << cells.size() << std::endl;
   exit(0);
}

std::vector<S6> GetCellsFromCellData(const std::vector<CellInputData>& cellData) {
   std::vector<S6> v;
   std::cout << "enter GetCellsFromCellData, cell count = " << cellData.size() << std::endl;
   for (unsigned long i = 0; i < cellData.size(); ++i)  v.push_back(cellData[i].GetCell());

   return v;
}

std::vector<std::vector<double> > BuildMatrix( const std::vector<double>& v ) {
   const unsigned long n = v.size();
   std::vector<std::vector<double> > vv(n, std::vector<double>(n, 0.0) );

   for ( unsigned long ii=0; ii<n; ++ii ) {
      for (unsigned long kk=0; kk<n; ++kk) {
         vv[ii][kk] = v[ii] * v[kk];
         vv[kk][ii] = vv[ii][kk];
      }
   }
   return vv;
}

int main()
{
   const std::vector<CellInputData> cellData = ReadAllLatticeData();  // read the data

   const unsigned long n = cellData.size();

   {
      // convert the input cells to Selling reduced cells
      auto start = std::clock();
      double elapsedTime;
      std::vector<S6> s6Reduced;
      start = std::clock();
      for (unsigned long i = 0; i < n; ++i) {
         const S6 sout = LatticeConverter::SellingReduceCell(cellData[i].GetLattice(), cellData[i].GetCell());
         s6Reduced.push_back(sout);
      }
      elapsedTime = std::clock() - start;
      std::cout << " Selling reduction  " << elapsedTime << std::endl;

      // compute the matrix of S6 distances
      std::vector<std::vector<double> >  s6Dist(n, std::vector<double>(n, 0.0));
      start = std::clock();
      for (unsigned long i = 0; i < n; ++i) {
         for (unsigned long k = i; k < n; ++k) {
            s6Dist[i][k] = CS6Dist(s6Reduced[i].data(), s6Reduced[k].data());
            s6Dist[k][i] = s6Dist[i][k];
         }
      }
      elapsedTime = std::clock() - start;
      std::cout << " CS6Dist distance matrix  " << elapsedTime << std::endl;
      //std::cout << " CS6Dist distance matrix  " << LRL_ToString(s6Dist) << std::endl;
   }

   {
      // convert the input cells to Niggli reduced cells
      auto start = std::clock();
      double elapsedTime;
      std::vector<G6> nigReduced;
      start = std::clock();
      for (unsigned long i = 0; i < n; ++i) {
         const G6 gout = LatticeConverter::NiggliReduceCell(cellData[i].GetLattice(), cellData[i].GetCell());
         nigReduced.push_back(gout);
      }
      elapsedTime = std::clock() - start;
      std::cout << " Niggli reduction  " << elapsedTime << std::endl;

      // compute the matrix of NCDist distances
      std::vector<std::vector<double> >  ngDist(n, std::vector<double>(n, 0.0));
      start = std::clock();
      for (unsigned long i = 0; i < n; ++i) {
         if ( i%20 == 0 ) std::cout << " i " << i << std::endl;
         for (unsigned long k = i; k < n; ++k) {
            ngDist[i][k] = NCDist(nigReduced[i].data(), nigReduced[k].data());
            ngDist[k][i] = ngDist[i][k];
         }
      }
      elapsedTime = std::clock() - start;
      std::cout << " NCDist distance matrix  " << elapsedTime << std::endl;
      //std::cout << " NCDist distance matrix  " << LRL_ToString(ngDist) << std::endl;
   }

   exit(0);

   //std::cout << cells.size() << std::endl;
   //if (!cells.empty())
   //   CheckReduceAndDistanceTiming(cells);
   return 0;
}

