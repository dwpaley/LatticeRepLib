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

int main()
{
   const std::vector<CellInputData> cellData = ReadAllLatticeData();
   std::cout << cellData.size() << std::endl;
   const std::vector<S6> cells = GetCellsFromCellData(cellData);
   std::cout << cells.size() << std::endl;
   if (!cells.empty())
      CheckReduceAndDistanceTiming(cells);
   return 0;
}

