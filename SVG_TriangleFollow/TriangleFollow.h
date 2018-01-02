#ifdef _MSC_VER
#define USE_LOCAL_HEADERS
#endif

#ifndef TRIANGLEFOLLOW_H
#define TRIANGLEFOLLOW_H

#include <iomanip>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "LRL_CreateFileName.h"
#include "Delone.h"
#include "S6Dist.h"
#include "D7Dist.h"
#include "GlobalTriangleFollowerConstants.h"
#include "haar.hpp"
#include "ProgressData.h"
#include "SVG_Tools.h"
#include "SVG_FollowTriangle.h"
#include "TriangleFollowTools.h"
#include "triple.h"

template<typename TVEC, typename TREDUCEMETHOD, typename TFOLLOWMETHOD> class SVG_FollowTriangle;

template<typename TVEC, typename TREDUCEMETHOD, typename TFOLLOWMETHOD>
class TriangleFollow
{
public:

   TriangleFollow<TVEC, TREDUCEMETHOD, TFOLLOWMETHOD >(const int seed, const int trialNumber, const int npoints)
      : m_fileNameFragment(LRL_CreateFileName::Create("FT_", ""))
      , m_points(npoints)
      , m_worstViolationFound(-DBL_MAX)
      , m_seed(seed)
      , m_trialNumber(trialNumber)
   {
      SetMinMaxX(1, npoints);
   }

   void clear()
   {
      for (unsigned long i = 0; i < 3; ++i) {
         m_followData[i].clear();
         m_dist23Delta[i].clear();
         m_dist13[i].clear();
         m_dist23[i].clear();
         m_angleDiff[i].clear();
         m_triangleDiff[i].clear();
         m_triangleArea[i].clear();
         m_tanhDist23Delta[i].clear();
         m_dist12[i].clear();
         m_dist13[i].clear();
         m_dist23[i].clear();
         m_normedDist23[i].clear();
         m_followData[i].resize(3);
         m_dist23Delta[i].resize(3);
         m_dist13[i].resize(3);
         m_dist23[i].resize(3);
         m_angleDiff[i].resize(3);
         m_triangleDiff[i].resize(3);
         m_triangleArea[i].resize(3);
         m_tanhDist23Delta[i].resize(3);
         m_dist12[i].resize(3);
         m_dist13[i].resize(3);
         m_dist23[i].resize(3);
         m_normedDist23[i].resize(3);
      }

   }

   std::string Follow(const TVEC& vin1, const TVEC& vin2, const TVEC& vin3, const double minimumPercentViolationToReport) {
      m_inputVector1 = vin1;
      m_inputVector2 = vin2;
      m_inputVector3 = vin3;

      m_maxRawDistance = ScalingInitialPoint(1.0, vin1, vin2, vin3);

      clear();
      //   SetMinMaxX( 1000, 2000 );
      std::ofstream folOut;
      std::string sFileName(GetFileNameFragment() + "log");
#ifdef DEBUGLOG
      folOut.open(sFileName.c_str(), std::ios::out);

      if (!folOut.is_open()) {
         std::cout << "Could not open file " << sFileName << " for write" << std::endl;
      }
#endif
      std::string svgTriangles;
      bool b = CreateVectorList("first line, point 1 constant, followed by 2,3 ", vin1, vin2, vin3, m_points);

      if (b) {
         const std::string svg1 = SetProgressData(folOut, m_points, "(first line, point 1 constant, followed by 2,3, blue)", m_dist23Delta[0], m_tanhDist23Delta[0], m_angleDiff[0], m_triangleDiff[0], m_triangleArea[0],
            m_normedDist23[0], m_dist12[0], m_dist13[0], m_dist23[0]);
         svgTriangles += svg1;

         b = CreateVectorList("second line, point 1 constant, followed by 1,2 ", vin3, vin1, vin2, m_points);
         if (b) {
            const std::string  svg2 = SetProgressData(folOut, m_points, "(second line, point 1 constant, followed by 1,2, orange)", m_dist23Delta[1], m_tanhDist23Delta[1], m_angleDiff[1], m_triangleDiff[1], m_triangleArea[1],
               m_normedDist23[1], m_dist12[1], m_dist13[1], m_dist23[1]);
            svgTriangles += svg2;

            b = CreateVectorList("third line, point 1 constant, followed by3,1", vin2, vin3, vin1, m_points);
            if (b) {
               const std::string svg3 = SetProgressData(folOut, m_points, "(third line, point 1 constant, followed by3,1, black)", m_dist23Delta[2], m_tanhDist23Delta[2], m_angleDiff[2], m_triangleDiff[2], m_triangleArea[2],
                  m_normedDist23[2], m_dist12[2], m_dist13[2], m_dist23[2]);
               svgTriangles += svg3;

               //ReportTriangleResults(folOut, "Del23", "DELTA DIST23",m_dist23Delta);
               //ReportTriangleResults(folOut, "Angle", "ANGLE DIFFERENCE BETWEEN LARGEST AND SMALLEST",m_angleDiff);
               //ReportTriangleResults(folOut, "Viol", "TRIANGLE VIOLATION PERCENT",m_triangleDiff);
               //ReportTriangleResults(folOut, "Area", "TRIANGLE AREA",m_triangleArea);
               //ReportTriangleResults(folOut, "tanh", "TANH DELTA DIST23",m_tanhDist23Delta);

               const int boxWidth = 1800;
               const int boxHeight = (boxWidth * 1600) / 1800;
               const int border = (boxWidth * 30) / 1800;;


               if (m_worstViolationFound >= minimumPercentViolationToReport) {
                  SVG_FollowTriangle<TVEC, TREDUCEMETHOD, TFOLLOWMETHOD> svg_FT(boxWidth, boxHeight, border, svgTriangles, *this);
                  this->m_OutputFilename = svg_FT.GetOutputFilename();
               }
            }
         }
      }

      return svgTriangles;
   }

   std::string PrepareTrianglesOutput(const std::string& label, const FollowVectors<TVEC>& vin1,
      const FollowVectors<TVEC>& vin2, const FollowVectors<TVEC>& vin3, const ProgressData<double>& area) {
      std::string svg;
      svg += "  start  " + label + "\n";
      const unsigned long nmax = maxNC(vin1.size(), vin2.size(), vin3.size());
      for (unsigned long i = 0; i < nmax; ++i) {
         const TVEC& v1(vin1[i]);
         const TVEC& v2(vin2[i]);
         const TVEC& v3(vin3[i]);
         svg += LRL_ToString(v1, "\n");
         svg += LRL_ToString(v2, "\n");
         svg += LRL_ToString(v3, "\n");
         //const std::string s1= LRL_ToString(vin1[i], "\n");
         //const std::string s2= LRL_ToString(vin2[i], "\n");
         //const std::string s3= LRL_ToString(vin3[i], "\n");
         const double dist12 = DIST(v1, v2);
         const double dist13 = DIST(v1, v3);
         const double dist23 = DIST(v2, v3);
         //const std::string s1a = LRL_ToString(v1);
         //const std::string s2a = LRL_ToString(v2);
         //const std::string s3a = LRL_ToString(v3);

         svg += LRL_ToString(" distances 12,13,23 ", dist12, dist13, dist23, "\n");
         if (area[i] > 0)
         {
            svg += LRL_ToString("====  ", label, i + 1, "\n");
         }
         else
         {
            svg += LRL_ToString("====  ", label, i + 1, "     ************negative area*************\n");
         }
      }
      svg += LRL_ToString("  end    ", label, "\n\n");

      return svg;
   }

   double ScalingInitialPoint(const double targetScale, const TVEC& v1, const TVEC& v2, const TVEC& v3) {
      const double d12 = TVEC(v1 - v2).norm();
      const double d13 = TVEC(v1 - v3).norm();
      const double d23 = TVEC(v2 - v3).norm();
      const double dmax = maxNC(d12, d13, d23);
      return targetScale / dmax;
   }

   bool CreateVectorList(const std::string& label, const TVEC& vin1, const TVEC& vin2, const TVEC& vin3, const int npoints)
   {
      m_followData[0].clear();
      m_followData[1].clear();
      m_followData[2].clear();
      const double maxd = ScalingInitialPoint(1.0, vin1, vin2, vin3);
      const TVEC v1(vin1/**1.0 / maxd*/);
      const TVEC v2(vin2/**1.0 / maxd*/);
      const TVEC v3(vin3/**1.0 / maxd*/);
      const double minFactor = 0.01;   /// FOR HJB
      const double maxFactor = double(m_maxX - 1) / double(npoints - 1);
      const double smallestFactorAllowed = 0.001 / double(npoints - 1);
      const double deltaFactor = (maxFactor - minFactor) / double(npoints - 1);
      double factor = std::max(minFactor, smallestFactorAllowed);

      const TVEC centerPoint(v1);

      S6 reducedCenterPoint;  // used in Niggli::Reduce
      MatS6 m;
      const bool btemp = TREDUCEMETHOD::Reduce(S6(centerPoint), m, reducedCenterPoint, 0.0);

      if (btemp) {
         for (int i = 0; i < npoints; ++i)
         {
            const double factorM = 1.0 - factor;;
            S6 red2, red3;  // used in Niggli::Reduce
            S6 red2A, red3A;  // used in Niggli::Reduce
            const bool btemp2 = TREDUCEMETHOD::Reduce(S6(factorM*centerPoint + factor*v2), m, red2, 0.0);
            const bool btemp3 = TREDUCEMETHOD::Reduce(S6(factorM*centerPoint + factor*v3), m, red3, 0.0);
            factor += deltaFactor;
            if (btemp2 && btemp3) {
               m_followData[0].push_back(TVEC(reducedCenterPoint) / factor);;   /// FOR HJB
               m_followData[1].push_back(TVEC(red2) / factor);;   /// FOR HJB
               m_followData[2].push_back(TVEC(red3) / factor);;   /// FOR HJB
            }
         }
      }

      return btemp;
   }

   static double DIST(const D7& v1, const D7& v2) {
      return D7Dist(v1.GetVector().data(), v2.GetVector().data());
   }

   static double DIST(const S6& v1, const S6& v2) {
      S6Dist s6dist(50000.0);
      return s6dist.DistanceBetween(v1, v2);
   }

   static double DIST(const B4& v1, const B4& v2) {
      throw; // not implement for Delone scalars
             //double a1[6], a2[6];
             //ProjectorTools::ConvertB4ToArray(v1, a1);
             //ProjectorTools::ConvertB4ToArray(v2, a2);
             //return B4Dist(a1, a2);
      return -19191.;
   }

   std::string SetProgressData(std::ostream& folOut, const int npoints, const std::string& label,
      ProgressData<double>& dist23Delta,
      ProgressData<double>& tanhdist23Delta,
      ProgressData<double>&  angleDiff,
      ProgressData<double>& triangleDiff,
      ProgressData<double>& triangleArea,
      ProgressData<double>& normedDist23,
      ProgressData<double>& vdist12,
      ProgressData<double>& vdist13,
      ProgressData<double>& vdist23) {

      angleDiff.clear();
      triangleDiff.clear();
      triangleArea.clear();
      vdist12.clear();
      vdist13.clear();
      vdist23.clear();
      dist23Delta.clear();
      normedDist23.clear();
      tanhdist23Delta.clear();

      double sumDeltaDist23 = 0.0;
      double prevDist23 = 0.0;
      int worstViolationIndex = -INT_MAX;
      double worstViolation = -DBL_MAX;
      //      const unsigned long dataPointCount = maxNC(m_data.sl1.size(), m_data.sl2.size(), m_data.sl3.size());
      const unsigned long dataPointCount = (unsigned long)maxNC(m_followData[0].size(), m_followData[1].size(), m_followData[2].size());
      for (unsigned long i = 0; i < dataPointCount; ++i)
      {
         const double dist12(DIST(m_followData[0][i], m_followData[1][i]));
         const double dist13(DIST(m_followData[0][i], m_followData[2][i]));
         const double dist23(DIST(m_followData[1][i], m_followData[2][i]));
         sumDeltaDist23 += dist23;
         const double maxDist = maxNC(dist12, dist13, dist23);
         const double trianglediff(100.0*(2.0*maxDist - (dist12 + dist13 + dist23)) / maxDist);
         if (trianglediff > worstViolation) {
            worstViolation = trianglediff;
            worstViolationIndex = i;
         }
         const double testDiff = 100.0*FollowerTools::TriangleInequality(dist12, dist13, dist23);
         double test = trianglediff - testDiff;
         const double absTest = std::abs(test);
         const double anglediff(AngleDiffFromSides(dist12, dist13, dist23));
         const double maxCosineDiff = MaxCosineDelta(dist12, dist13, dist23);

         const double area(SqrtTriangleAreaFromSides(dist12, dist13, dist23));
         const double deltaDist23 = dist23 - prevDist23;
         vdist12.push_back(dist12);
         vdist13.push_back(dist13);
         vdist23.push_back(dist23);



         const double factor = std::max(double(i), 1.0) / double(dataPointCount - 1);
         const double normalizer23 = (m_maxRawDistance * factor);
         normedDist23.push_back(dist23 / normalizer23);

         if (worstViolation > m_worstViolationFound) {
            m_worstViolationFound = worstViolation;
            m_worstVec1 = m_followData[0][worstViolationIndex];
            m_worstVec2 = m_followData[1][worstViolationIndex];
            m_worstVec3 = m_followData[2][worstViolationIndex];
         }

         angleDiff.push_back(anglediff);
         triangleDiff.push_back(trianglediff);
         triangleArea.push_back(area);
      }

      std::string svg;
      svg += PrepareTrianglesOutput(label, m_followData[0], m_followData[1], m_followData[2], triangleArea);

      const double filterValue = 500.0;
      std::vector<double> vtemp = MakeHaarOfDeltas(filterValue, normedDist23.GetVector());
      dist23Delta.SetVector(vtemp);
      dist23Delta.push_back(0.0);


      double maxAbsDeltaDist23 = GetMaxAbsValue(dist23Delta.GetVector());

      const double averageDeltaDist23 = sumDeltaDist23 / dataPointCount;
      const double factor = GetOptimalFactor(maxAbsDeltaDist23, averageDeltaDist23, 0.95);

      for (unsigned long i = 0; i < dist23Delta.size(); ++i)
         tanhdist23Delta.push_back(TanhValue(dist23Delta[i], averageDeltaDist23, factor));

      for (unsigned long i = 0; i < dist23Delta.size() - 1; ++i) {
         //  LCA
         if (std::abs(triangleDiff[i]) > 0.1) {
            const unsigned long startPoint = std::max(0UL, i);
            const unsigned long tanhSize = triangleDiff.size();
            const unsigned long endPoint = std::min(tanhSize, i + 4);
            double maxLocalValue = 0.0;
            double signedLocalMax = 0.0;
            for (unsigned long point = startPoint + 1; point < endPoint; ++point) {
               if (std::abs(triangleDiff[point]) > maxLocalValue) {
                  maxLocalValue = std::abs(triangleDiff[point]);
                  signedLocalMax = triangleDiff[point];
               }
            }

            //        if (maxLocalValue < 0.5 *std::abs(triangleDiff[i]) || triangleDiff[i] * signedLocalMax < 0.0) {
            //if (std::abs(triangleDiff[i] - triangleDiff[i + 1])> 0.01*(std::abs(triangleDiff[i]) + std::abs(triangleDiff[i + 1]))) {
            if (std::abs(triangleDiff[i] - triangleDiff[i + 1]) > GlobalConstants::globalAboveThisValueIsBad) { // triangleDiff is in percent
               //for (unsigned long point = startPoint; point < endPoint; ++point) {
               //   const std::string s(LogWork(point, label, m_followData[0][point], m_followData[1][point], m_followData[2][point], vdist12[point], vdist13[point], vdist23[point], angleDiff[point], triangleDiff[point], triangleArea[point]));
               //   m_ProblemLog.push_back(s);
               //}
               //m_ProblemLog.push_back("==============================================");
            }
         }
      }
      //normedDist23.SetPointIsError( tanhdist23Delta.GetVector() );
      return svg;
   }

   std::string GetFileNameFragment(void) const { return m_fileNameFragment; }
   int GetMinX(void) const { return m_minX; }
   int GetMaxX(void) const { return m_maxX; }

   triple<TVEC, TVEC, TVEC> GetWorstTriple(void) const {
      return triple<TVEC, TVEC, TVEC>(m_worstVec1, m_worstVec2, m_worstVec3);
   }


   std::string GetOutputFilename(void) const {
      return m_OutputFilename;
   }

   double GetMaxRawDistance(void) const { return m_maxRawDistance; }
   int GetSeed(void) const { return m_seed; }
   int GetTrialNumber(void) const { return m_trialNumber; }
   TVEC GetWorstVector1(void) const { return m_worstVec1; }
   TVEC GetWorstVector2(void) const { return m_worstVec2; }
   TVEC GetWorstVector3(void) const { return m_worstVec3; }

   TVEC m_inputVector1;
   TVEC m_inputVector2;
   TVEC m_inputVector3;

   FollowVectors<TVEC>  m_followData[3];
   ProgressData<double> m_normedDist23[3];
   ProgressData<double> m_dist23Delta[3];
   ProgressData<double> m_tanhDist23Delta[3];
   ProgressData<double> m_angleDiff[3];
   ProgressData<double> m_triangleDiff[3];
   ProgressData<double> m_triangleArea[3];
   ProgressData<double> m_dist12[3];
   ProgressData<double> m_dist13[3];
   ProgressData<double> m_dist23[3];

   std::vector<std::string> m_ProblemLog;
   int m_minX;
   int m_maxX;

private:
   const int m_points;
   const std::string m_fileNameFragment;
   double m_worstViolationFound;
   std::string m_OutputFilename;
   double m_maxRawDistance;
   TVEC m_worstVec1;
   TVEC m_worstVec2;
   TVEC m_worstVec3;
   const int m_seed;
   const int m_trialNumber;

public:
   //void ReportTriangleResults( std::ostream& folOut, const std::string& prefix, const std::string& label, const Triple<double>& t );
   void ReportTriangleResults(std::ostream& folOut, const std::string& prefix, const std::string& label, const ProgressData<double> t[3])/*;

static void ReportTriangleResults( std::ostream& folOut, const std::string& prefix, const std::string& label, const TVEC& t ) */ {
      folOut << std::endl << label << std::endl;
      const unsigned long n1 = t[0].size();
      const unsigned long n2 = t[1].size();
      const unsigned long n3 = t[2].size();

      const unsigned long n = maxNC(n3, n1, n2);
      for (unsigned long i = 0; i < n; ++i)
         folOut << prefix << " " << i << "  " <<
         ((i < n1) ? LRL_ToString(t[0][i]) : "XXXX") + "  "
         + ((i < n2) ? LRL_ToString(t[1][i]) : "XXXX") + "  "
         + ((i < n3) ? LRL_ToString(t[2][i]) : "XXXX") << std::endl;
   }


   void SetMinMaxX(const int minX, const int maxX) { m_minX = minX; m_maxX = maxX; }

   void WorstTriangleViolation(const Triple<double>& triangleDiff) {
      const std::vector<double>::const_iterator it1 = std::max_element(triangleDiff.sl1.begin(), triangleDiff.sl1.end());
      const std::vector<double>::const_iterator it2 = std::max_element(triangleDiff.sl2.begin(), triangleDiff.sl2.end());
      const std::vector<double>::const_iterator it3 = std::max_element(triangleDiff.sl3.begin(), triangleDiff.sl3.end());

      std::cout << "worst tri-d 1 " << *it1 << std::endl;
      std::cout << "worst tri-d 2 " << *it2 << std::endl;
      std::cout << "worst tri-d 3 " << *it3 << std::endl;

      if (*it1 > std::max(*it2, *it3)) FindWorstInSeries(triangleDiff.sl1.begin(), it1);
      else if (*it2 > *it3)            FindWorstInSeries(triangleDiff.sl2.begin(), it2);
      else                             FindWorstInSeries(triangleDiff.sl3.begin(), it3);
   }

   void FindWorstInSeries(const std::vector<double>::const_iterator& seriesBegin, const std::vector<double>::const_iterator it) {
      const int n = std::distance(seriesBegin, it);
      std::cout << n << std::endl;
      m_worstVec1 = m_followData[2][n];
      m_worstVec2 = m_followData[2][n];
      m_worstVec3 = m_followData[2][n];
   }

private:

   static std::vector<double> MakeHaarOfDeltas(const double slack, const std::vector<double>& v) {
      const unsigned long n = (unsigned long)v.size();
      const unsigned long nMinusOne = (n == 0) ? 1 : n - 1;;
      std::vector<double> ar1(nMinusOne);

      for (unsigned long i = 1; i < n; ++i) ar1[i - 1] = v[i] - v[i - 1];

      haar_1d(nMinusOne, ar1);

      //   for( unsigned long i = 0; i<unsigned long(nMinusOne*0.8); ++i) ar1[i] = 0.0;

      const double maxv = *std::max_element(ar1.begin(), ar1.end());

      for (unsigned long i = 0; i < nMinusOne; ++i) if (std::abs(ar1[i]) < maxv / slack) ar1[i] = 0.0;
      ar1[0] = 0.0;

      haar_1d_inverse(nMinusOne, ar1);
      return ar1;
   }

   static std::vector<double> MakeHaar(const double slack, const std::vector<double>& v) {
      const unsigned long n = v.size();
      std::vector<double> ar1(v);

      haar_1d(n, ar1);

      double maxv = 0.0;
      for (unsigned long i = 0; i < n; ++i) maxv = std::max(std::abs(ar1[i]), maxv);

      for (unsigned long i = 0; i < n; ++i) if (std::abs(ar1[i]) < maxv / slack) ar1[i] = 0.0;
      ar1[0] = 0.0;

      haar_1d_inverse(n, ar1);
      return ar1;
   }

   static double TanhValue(const double inputValue, const double averageDeltaDist23, const double factor) {
      return tanh(factor*inputValue / averageDeltaDist23);
   }

   static double GetOptimalFactor(const double maxAbsDeltaDist23, const double averageDeltaDist23, const double targetTanhValue) {
      double factor = 0.2;
      int count = 0;
      while (std::abs(TanhValue(maxAbsDeltaDist23, averageDeltaDist23, factor) < targetTanhValue) && count++ < 500)
         factor *= 1.1;
      return factor;
   }

   static double GetMaxAbsValue(const std::vector<double>& valueList) {
      const std::vector<double>::const_iterator start = valueList.begin();
      const std::vector<double>::const_iterator end = valueList.end();
      return std::max(std::abs(*std::min_element(start, end)),
         std::abs(*std::max_element(start, end)));
   }

   static std::string PrintHighPrecisionArrayVectorData(const std::string& label, const double ar[]) {
      std::ostringstream ostr;
      ostr << std::setprecision(16) << label << " "
         << ar[0] << " "
         << ar[1] << " "
         << ar[2] << " "
         << ar[3] << " "
         << ar[4] << " "
         << ar[5] << std::endl;
      return ostr.str();
   }

   static double DifferenceOfCosinesOfTwoAngles(const double cos1, const double cos2) {
      const double sinSq1 = 1.0 - cos1*cos1;
      const double sinSq2 = 1.0 - cos2*cos2;
      if ((sinSq1 < 0.0 && sinSq2 < 0.0) ||
         (sinSq1 > 0.0 && sinSq2 > 0.0) ||
         (sinSq1 == 0.0 || sinSq2 == 0.0))
         return std::sqrt(sinSq1*sinSq2) + cos1*cos2;
      else // here, one and only one sinSq is negative, so we're in complex plane
         return std::sqrt(-sinSq1*sinSq2 + cos1*cos2*cos1*cos2);
   }

   static double MaxCosineDelta(const double dist12, const double dist13, const double dist23) {
      const double cos12 = AngleCosineFromSides(dist12, dist13, dist23);
      const double cos13 = AngleCosineFromSides(dist13, dist23, dist12);
      const double cos23 = AngleCosineFromSides(dist23, dist12, dist13);

      const double sinsq12 = 1.0 - cos12*cos12;
      const double sinsq13 = 1.0 - cos13*cos13;
      const double sinsq23 = 1.0 - cos23*cos23;

      const double anglediff1(DifferenceOfCosinesOfTwoAngles(cos12, cos13));
      const double anglediff2(DifferenceOfCosinesOfTwoAngles(cos12, cos23));
      const double anglediff3(DifferenceOfCosinesOfTwoAngles(cos23, cos13));
      return maxNC(anglediff1, anglediff2, anglediff3);
   }

};

#endif
