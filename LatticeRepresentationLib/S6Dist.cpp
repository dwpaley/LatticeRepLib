
#include "stdafx.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <utility>

#include "Delone.h"
#include "LRL_inverse.h"
#include "LRL_ToString.h"
#include "S6Dist.h"


std::vector< S6(*)(const S6&)> S6Dist::m_reductionFunctions;
std::vector< S6(*)(const S6&)> S6Dist::m_UnReduceFunctions;

std::vector< std::pair<S6(*)(const S6&), S6(*)(const S6&)> > S6Dist::SetUnreduceFunctionPairs() {
   std::vector< std::pair<S6(*)(const S6&), S6(*)(const S6&)> > vf;
   vf.push_back(std::make_pair(S6Dist::Unreduce11, S6Dist::Unreduce12));
   vf.push_back(std::make_pair(S6Dist::Unreduce21, S6Dist::Unreduce22));
   vf.push_back(std::make_pair(S6Dist::Unreduce31, S6Dist::Unreduce32));
   vf.push_back(std::make_pair(S6Dist::Unreduce41, S6Dist::Unreduce42));
   vf.push_back(std::make_pair(S6Dist::Unreduce51, S6Dist::Unreduce52));
   vf.push_back(std::make_pair(S6Dist::Unreduce61, S6Dist::Unreduce62));
   return vf;
}

void S6Dist::SetReduceFunctions() {
   m_reductionFunctions.push_back(S6Dist::Reduce11);
   m_reductionFunctions.push_back(S6Dist::Reduce21);
   m_reductionFunctions.push_back(S6Dist::Reduce31);
   m_reductionFunctions.push_back(S6Dist::Reduce41);
   m_reductionFunctions.push_back(S6Dist::Reduce51);
   m_reductionFunctions.push_back(S6Dist::Reduce61);
}

void S6Dist::SetUnreduceFunctions() {
   m_UnReduceFunctions.push_back(S6Dist::Unreduce11);
   m_UnReduceFunctions.push_back(S6Dist::Unreduce21);
   m_UnReduceFunctions.push_back(S6Dist::Unreduce31);
   m_UnReduceFunctions.push_back(S6Dist::Unreduce41);
   m_UnReduceFunctions.push_back(S6Dist::Unreduce51);
   m_UnReduceFunctions.push_back(S6Dist::Unreduce61);
}

S6Dist::S6Dist(const double dnearzero/* = 1.0*/)
   : m_nearzero(dnearzero)
   , m_debug(false)
{
   SetReduceFunctions();
   SetUnreduceFunctions();
}

S6 S6Dist::ApplyReductionFunction(const unsigned long n, const S6& d) const {
   const S6 dred(m_reductionFunctions[n](d));
   return dred;
}

S6 S6Dist::ApplyUnreduceFunction(const unsigned long n, const S6& d) const {
   const S6 dred(m_UnReduceFunctions[n](d));
   return dred;
}

void PrintVector(const std::vector<S6>& v1, const std::vector<S6>& v2) {
   S6Dist s6dist(50000.0);
   for (unsigned long i = 0; i < v2.size(); ++i) {
      const std::pair<double, unsigned long> p = s6dist.MinForListOfS6(DBL_MAX, v2[i], v1);
      std::cout << v2[i] << "              " << p.first << "   (" << p.second << "," << i << ")" << std::endl;
   }

}


void PrintVector(const std::vector<S6>& v) {
   for (unsigned long i = 0; i < v.size(); ++i) {
      std::cout << v[i] << std::endl;
   }
}

void PrintVector(const S6 v1, const std::vector<S6>& v2) {
   for (unsigned long i = 0; i < v2.size(); ++i) {
      std::cout << v2[i] << "              " << (v1, v2[i]).norm() << std::endl;
   }
}

void S6Dist::UnreduceAndAddToList(const S6& d, const unsigned long n, std::vector<S6>& v) const {
   const unsigned long vsize = (unsigned long)v.size();
   for (unsigned long i = 0; i < vsize; ++i) {
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! LCA
      S6 dtemp = ApplyUnreduceFunction(n, d);
      //S6 dtemp(v[i]);
      //dtemp[n] = 0.001 * dtemp.norm();
      v.push_back(dtemp);
   }
}

const double g_percent = 0.10;

std::vector<S6> S6Dist::UnreduceAndAddToList(const std::vector<S6>& v6, const unsigned long n) const {
   std::vector<S6> vToReduce(v6);
   if (n > 0) {
      for (unsigned long k = 0; k < v6.size(); ++k) {
         const double d = v6[k].norm();
         for (unsigned long i = 0; i < 6; ++i) {
            if (v6[k][i] > -d * g_percent && v6[k][i] <= 0.0) {
               S6 stemp = ApplyUnreduceFunction(i, v6[k]);
               vToReduce.push_back(stemp);
            }
         }
      }
      vToReduce = UnreduceAndAddToList(vToReduce, n - 1);
   }
   return vToReduce;
}

std::vector<S6> S6Dist::UnreduceAndAddToList(const S6& s6, const unsigned long n) const {
   std::vector<S6> vToReflect;
   vToReflect.push_back(s6);
   return UnreduceAndAddToList(vToReflect, n);
   return vToReflect;
}

std::vector<S6> S6Dist::ResetNearZeroAndAddToList(const std::vector<S6>& v6, const unsigned long n) const {
   std::vector<S6> vToReduce(v6);
   if (n > 0) {
      for (unsigned long k = 0; k < v6.size(); ++k) {
         const double d = v6[k].norm();
         for (unsigned long i = 0; i < 6; ++i) {
            if (v6[k][i] > -d* g_percent && v6[k][i] <= 0.0) {
               S6 stemp = v6[k];
               stemp[i] = 0.1;
               vToReduce.push_back(stemp);
               //S6 out;
               //const bool b = Selling::Reduce(stemp, out);
               //if (b) vToReduce.push_back(out);
            }
         }
      }
   }
   return vToReduce;
}

std::vector<S6> S6Dist::ResetNearZeroAndAddToList(const S6& s6, const unsigned long n) const {
   std::vector<S6> vToReflect(1,s6);
   vToReflect = ResetNearZeroAndAddToList(vToReflect, n);
   //std::cout << LRL_ToString(vToReflect) << std::endl;
   return vToReflect;
}

std::vector<S6> S6Dist::GenerateReflectionsAtZero(const S6& s6) const {
   std::vector<S6> vToReflect;
   vToReflect.push_back(s6);

   const double d = s6.norm();
   for (unsigned long i = 0; i < 6; ++i) {
      if (s6[i] > -d*g_percent && s6[i] <= 0.0) {
         UnreduceAndAddToList(s6, i, vToReflect);
      }
   }

   const unsigned long vsize = (unsigned long)vToReflect.size();
   for (unsigned long i = 0; i < vsize; ++i) {
      for (unsigned long k = 0; k < 24; ++k) {
         vToReflect.push_back(MatS6::GetReflection(k) * vToReflect[i]);
      }
   }

   return vToReflect;
}

StoreResults<double, std::string> g_debug(1);
std::pair<double, unsigned long> S6Dist::MinForListOfS6(const std::vector<S6>& v1, const CNearTree<S6>& tree) const {
   g_debug.clear();
   g_debug.SetTitle("    *************** *************** *************** *************** S6 Distance Calculations ********************");
   g_debug.SetFooter("    *************** *************** *************** END END END END S6 Distance Calculations ********************");
   S6 s6min(tree[0]);
   double dmin = (v1[0] - s6min).norm();
   std::pair<double, unsigned long> p = std::make_pair(dmin, 0);
   const std::string itemA = LRL_ToString(v1[0]) + std::string("\n") + LRL_ToString(s6min);
   g_debug.Store(dmin, itemA);
   for (unsigned long i = 0; i < v1.size(); ++i) {
      const CNearTree<S6>::iterator it = tree.NearestNeighbor(dmin, v1[i]);
      if (it != tree.end()) {
         const double test = (*it)[0];
         std::string item;
         if (m_debug /*&& it != tree.end()*/) {
            item = LRL_ToString(v1[i]) + std::string("\n") + LRL_ToString(*it);
            g_debug.Store(std::min(dmin, (v1[i] - (*it)).norm()), item);
         }
         if (it != tree.end()) {
            const double first = (*it)[0];
            const double dist = (v1[i] - (*it)).norm();
            std::pair<double, unsigned long> ptemp = std::make_pair(dist, 0);
            if (ptemp.first < dmin) {
               p.second = i;
               p.first = ptemp.first;
               dmin = p.first;
               s6min = *it;
            }
         }
         if (m_debug) {
            //std::cout << std::endl;
            //std::cout << v1[p.second] << std::endl;
            //std::cout << s6min << "    dmin A " << dmin  << std::endl;
         }
      }
   }
   if (m_debug) g_debug.ShowResultsByKey();
   return p;
}

std::pair<double, unsigned long> S6Dist::MinForListOfS6(const std::vector<S6>& v1, const std::vector<S6>& v2) const {
   g_debug.clear();
   g_debug.SetTitle("    *************** *************** *************** *************** S6 Distance Calculations ********************");
   g_debug.SetFooter("    *************** *************** *************** END END END END S6 Distance Calculations ********************");
   double dmin = DBL_MAX;
   std::pair<double, unsigned long> p = std::make_pair(dmin, 0);
   for (unsigned long iouter = 0; iouter < v1.size(); ++iouter) {
      std::pair<double, unsigned long> ptemp = MinForListOfS6(dmin, v1[iouter], v2);
      if (ptemp.first < dmin) {
         dmin = ptemp.first;
         p.second = iouter;
         p.first = ptemp.first;
      }
      if ( m_debug) std::cout << "dmin A " << dmin << std::endl;
   }
   if (m_debug) g_debug.ShowResultsByKey();
   return p;
}

std::pair<double, unsigned long> S6Dist::MinForListOfS6( const double dminSoFar, const S6& d1, const std::vector<S6>& v) const {
   double dmin = std::min(dminSoFar,(d1 - v[0]).norm());
   std::pair<double, unsigned long> p = std::make_pair(dmin, 0);
   for (unsigned long i = 0; i < v.size(); ++i) {
      double dtemp = (d1 - v[i]).norm();
      if (dtemp < dmin) {
         p = std::make_pair(dtemp, i);
         dmin = p.first;
      }
      if (m_debug) {
         const std::string item = LRL_ToString(d1) + std::string("\n") + LRL_ToString(v[i]);
         g_debug.Store(dmin, item);
      }
   }
   return p;
}

const std::vector<S6> S6Dist::Generate24Reflections(const S6& s6in) {
   std::vector<S6> v;
   for (unsigned long i = 0; i < 24; ++i) {
      v.push_back(MatS6::GetReflection(i) * s6in);
   }
   return v;
}

const std::vector<S6> S6Dist::Generate24Reflections(const std::vector<S6>& vin) {
   std::vector<S6> vout;
   for (unsigned long i = 0; i < vin.size(); ++i) {
      const std::vector<S6> vtemp = Generate24Reflections(vin[i]);
      vout.insert(vout.end(), vtemp.begin(), vtemp.end());
   }
   return vout;
}

double S6Dist::DistanceBetween(const S6& s1, const S6& s2) {
   return DistanceBetween1(s1, s2);
}

double S6Dist::DistanceBetween1(const S6& s1, const S6& s2) {
   const unsigned long n = 2;
   const std::vector<S6> vinside = ResetNearZeroAndAddToList(s1, 1);
   const std::vector<S6> voutside = Generate24Reflections(UnreduceAndAddToList(ResetNearZeroAndAddToList(s2, n), 1));
   if (m_debug) {
      std::cout << "vinside  " << vinside.size() << std::endl << LRL_ToString(vinside) << std::endl << std::endl;
      std::cout << "voutside " << voutside.size() << std::endl << LRL_ToString(voutside) << std::endl << std::endl;
   }
   const double smallest = MinForListOfS6(vinside, voutside).first;
   return smallest;
}

double S6Dist::DistanceBetween2(const S6& s1, const S6& s2) {
   const unsigned long n = 2;
   const std::vector<S6> vinside = UnreduceAndAddToList(s1, n);
   const std::vector<S6> voutside = Generate24Reflections(UnreduceAndAddToList(s2, n));
   const CNearTree<S6> tree = voutside;

   const double smallest = MinForListOfS6(vinside, tree).first;
   return smallest;
}

MatS6 Inverse(const MatS6& min) {
   MatS6 m(min);
   std::vector<double> arout(36);
   inverse(6, min.GetVector().data(), arout.data());
   m.SetVector(arout);
   return m;
}

std::vector<std::pair<MatS6, MatS6> > S6Dist::SetunreductionReductionMatricesFromReductionMatrices() {
   std::vector<std::pair<MatS6, MatS6> > vRed;

   // first and second of each are the two alternate unreduce matrices - related by a reflection

   vRed.push_back(std::make_pair(Inverse(MatS6("-1 0 0 0 0 0   1 1 0 0  0 0   1 0 0 0 1 0   -1 0 0 1 0 0   1 0 1 0 0 0   1 0 0 0 0 1")),
      Inverse(MatS6("-1 0 0 0 0 0   1 0 0 0  0 1   1 0 1 0 0 0   -1 0 0 1 0 0   1 0 0 0 1 0   1 1 0 0 0 0"))));  // g or p

   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 1 0 0 0 0   0 -1 0 0 0 0   0 1 0 1 0 0   0 1 1 0 0 0   0 -1 0 0 1 0   0 1 0 0 0 1")),
      Inverse(MatS6(" 0 1 0 0 0 1   0 -1 0 0 0 0   0 1 1 0 0 0   0 1 0 1 0 0   0 -1 0 0 1 0   1 1 0 0 0 0"))));  // h or q

   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 0 1 0 0 0   0  0 1 1 0 0   0 0 -1 0 0 0   0 1 1 0 0 0   0 0 1 0  1 0   0 0 -1 0 0 1")),
      Inverse(MatS6(" 0 0 1 0 1 0   0  1 1 0 0 0   0 0 -1 0 0 0   0 0 1 1 0 0   1 0 1 0  0 0   0 0 -1 0 0 1"))));  // k or r

   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 0 0 -1 0 0   0 0 1 1 0 0   0 1 0 1 0 0   0 0 0 -1 0 0   0 0 0 1 1 0   0 0 0 1 0 1")),
      Inverse(MatS6(" 1 0 0 -1 0 0   0 1 0 1 0 0   0 0 1 1 0 0   0 0 0 -1 0 0   0 0 0 1 0 1   0 0 0 1 1 0"))));  // l or s

   vRed.push_back(std::make_pair(Inverse(MatS6(" 0 0 1 0 1 0   0 1 0 0 -1 0   1 0 0 0 1 0   0 0 0 1 1 0   0 0 0 0 -1 0   0 0 0 0 1 1")),
      Inverse(MatS6(" 1 0 0 0 1 0   0 1 0 0 -1 0   0 0 1 0 1 0   0 0 0 0 1 1   0 0 0 0 -1 0   0 0 0 1 1 0"))));  // m or t

   vRed.push_back(std::make_pair(Inverse(MatS6(" 0 1 0 0 0 1   1 0 0 0 0 1   0 0 1 0 0 -1   0 0 0 1 0 1   0 0 0 0 1 1   0 0 0 0 0 -1")),
      Inverse(MatS6(" 1 0 0 0 0 1   0 1 0 0 0 1   0 0 1 0 0 -1   0 0 0 0 1 1   0 0 0 1 0 1   0 0 0 0 0 -1"))));  // n or u

   for (unsigned long i = 0; i < vRed.size(); ++i) {
      for (unsigned long k = 0; k < 36; ++k) {
         if (abs(vRed[i].first[k]) < 0.001) vRed[i].first[k] = 0.0;
         if (abs(vRed[i].second[k]) < 0.001) vRed[i].second[k] = 0.0;
      }
   }
   return vRed;
}

std::vector<std::pair<MatS6, MatS6> > S6Dist::SetUnreductionMatrices() {
   std::vector<std::pair<MatS6, MatS6> > vUnRed;

   // For unreducing scalar 11
   vUnRed.push_back(std::make_pair(MatS6(" -1 0 0 0 0 0    1 1 0 0 0 0    1 0 0 0 1 0 -1 0 0 1 0 0    1 0 1 0 0 0    1 0 0 0 0 1"),

      // For unreducing scalar 12
      MatS6(" -1 0 0 0 0 0    1 0 0 0 0 1    1 0 1 0 0 0 -1 0 0 1 0 0    1 0 0 0 1 0    1 1 0 0 0 0")));

   // For unreducing scalar 21
   vUnRed.push_back(std::make_pair(MatS6("1 1 0 0 0 0    0 -1 0 0 0 0    0 1 0 1 0 0    0 1 1 0 0 0    0 -1 0 0 1 0    0 1 0 0 0 1"),

      // For unreducing scalar 22
      MatS6("0 1 0 0 0 1    0 -1 0 0 0 0    0 1 1 0 0 0    0 1 0 1 0 0    0 -1 0 0 1 0    1 1 0 0 0 0")));

   // For unreducing scalar 31
   vUnRed.push_back(std::make_pair(MatS6("1 0 1 0 0 0    0 0 1 1 0 0    0 0 -1 0 0 0    0 1 1 0 0 0    0 0 1 0 1 0    0 0 -1 0 0 1"),

      // For unreducing scalar 32
      MatS6("0 0 1 0 1 0    0 1 1 0 0 0    0 0 -1 0 0 0    0 0 1 1 0 0    1 0 1 0 0 0    0 0 -1 0 0 1")));

   // For unreducing scalar 41
   vUnRed.push_back(std::make_pair(MatS6("1 0 0 -1 0 0    0 0 1 1 0 0    0 1 0 1 0 0    0 0 0 -1 0 0    0 0 0 1 1 0    0 0 0 1 0 1"),

      // For unreducing scalar 42
      MatS6("1 0 0 -1 0 0    0 1 0 1 0 0    0 0 1 1 0 0    0 0 0 -1 0 0    0 0 0 1 0 1    0 0 0 1 1 0")));

   // For unreducing scalar 51
   vUnRed.push_back(std::make_pair(MatS6("0 0 1 0 1 0    0 1 0 0 -1 0    1 0 0 0 1 0    0 0 0 1 1 0    0 0 0 0 -1 0    0 0 0 0 1 1"),

      // For unreducing scalar 52
      MatS6("1 0 0 0 1 0    0 1 0 0 -1 0    0 0 1 0 1 0    0 0 0 0 1 1    0 0 0 0 -1 0    0 0 0 1 1 0")));

   // For unreducing scalar 61
   vUnRed.push_back(std::make_pair(MatS6("0 1 0 0 0 1    1 0 0 0 0 1    0 0 1 0 0 -1    0 0 0 1 0 1    0 0 0 0 1 1    0 0 0 0 0 -1"),

      // For unreducing scalar 62
      MatS6("1 0 0 0 0 1    0 1 0 0 0 1    0 0 1 0 0 -1    0 0 0 0 1 1    0 0 0 1 0 1    0 0 0 0 0 -1")));

   return vUnRed;
}

S6 S6Dist::Reduce11(const S6& din) {
   // reduce scale 1 non-zero
   //   vRed.push_back(std::make_pair(Inverse(MatS6("-1 0 0 0 0 0   1 1 0 0  0 0   1 0 0 0 1 0   -1 0 0 1 0 0   1 0 1 0 0 0   1 0 0 0 0 1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s1;
   ss2 = s1 + s2;
   ss3 = s1 + s5;
   ss4 = -s1 + s4;
   ss5 = s1 + s3;
   ss6 = s1 + s6;
   return d;
}

S6 S6Dist::Reduce12(const S6& din) {
   // reduce scale 1 non-zero
   //                                 Inverse(MatS6("-1 0 0 0 0 0   1 0 0 0  0 1   1 0 1 0 0 0   -1 0 0 1 0 0   1 0 0 0 1 0   1 1 0 0 0 0"))));  // g or p
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s1;
   ss2 = s1 + s6;
   ss3 = s1 + s3;
   ss4 = -s1 + s4;
   ss5 = s1 + s5;
   ss6 = s1 + s2;
   return d;
}

S6 S6Dist::Reduce21(const S6& din) {
   // reduce scale 2 non-zero
   //   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 1 0 0 0 0   0 -1 0 0 0 0   0 1 0 1 0 0   0 1 1 0 0 0   0 -1 0 0 1 0   0 1 0 0 0 1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s2 + s6;
   ss2 = -s2;
   ss3 = s2 + s3;
   ss4 = s2 + s4;
   ss5 = -s2 + s5;
   ss6 = s2 + s1;
   return d;
}

S6 S6Dist::Reduce22(const S6& din) {
   // reduce scale 2 non-zero
   //                                 Inverse(MatS6(" 0 1 0 0 0 1   0 -1 0 0 0 0   0 1 1 0 0 0   0 1 0 1 0 0   0 -1 0 0 1 0   1 1 0 0 0 0"))));  // h or q
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s2 + s6;
   ss2 = -s2;
   ss3 = s2 + s3;
   ss4 = s2 + s4;
   ss5 = -s2 + s5;
   ss6 = s2 + s1;
   return d;
}

S6 S6Dist::Reduce31(const S6& din) {
   // reduce scale 3 non-zero
   //   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 0 1 0 0 0   0  0 1 1 0 0   0 0 -1 0 0 0   0 1 1 0 0 0   0 0 1 0  1 0   0 0 -1 0 0 1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s3 + s1;
   ss2 = s3 + s4;
   ss3 = -s3;
   ss4 = s3 + s2;
   ss5 = s3 + s5;
   ss6 = -s3 + s6;
   return d;
}

S6 S6Dist::Reduce32(const S6& din) {
   // reduce scale 3 non-zero
   //                                 Inverse(MatS6(" 0 0 1 0 1 0   0  1 1 0 0 0   0 0 -1 0 0 0   0 0 1 1 0 0   1 0 1 0  0 0   0 0 -1 0 0 1"))));  // k or r
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s3 + s5;
   ss2 = s3 + s2;
   ss3 = -s3;
   ss4 = s3 + s4;
   ss5 = s3 + s1;
   ss6 = -s3 + s6;
   return d;
}

S6 S6Dist::Reduce41(const S6& din) {
   // reduce scale 4 non-zero
   //   vRed.push_back(std::make_pair(Inverse(MatS6(" 1 0 0 -1 0 0   0 0 1 1 0 0   0 1 0 1 0 0   0 0 0 -1 0 0   0 0 0 1 1 0   0 0 0 1 0 1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s4 + s1;
   ss2 = s4 + s3;
   ss3 = s4 + s2;
   ss4 = -s4;
   ss5 = s4 + s5;
   ss6 = s4 + s6;
   return d;
}

S6 S6Dist::Reduce42(const S6& din) {
   // reduce scale 4 non-zero
   //                                 Inverse(MatS6(" 1 0 0 -1 0 0   0 1 0 1 0 0   0 0 1 1 0 0   0 0 0 -1 0 0   0 0 0 1 0 1   0 0 0 1 1 0"))));  // l or s
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s4 + s1;
   ss2 = s4 + s2;
   ss3 = s4 + s3;
   ss4 = -s4;
   ss5 = s4 + s6;
   ss6 = s4 + s5;
   return d;
}

S6 S6Dist::Reduce51(const S6& din) {
   // reduce scale 5 non-zero
   //   vRed.push_back(std::make_pair(Inverse(MatS6(" 0 0 1 0 1 0   0 1 0 0 -1 0   1 0 0 0 1 0   0 0 0 1 1 0   0 0 0 0 -1 0   0 0 0 0 1 1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s5 + s3;
   ss2 = -s5 + s2;
   ss3 = s5 + s1;
   ss4 = s5 + s4;
   ss5 = -s5;
   ss6 = s5 + s6;
   return d;
}

S6 S6Dist::Reduce52(const S6& din) {
   // reduce scale 5 non-zero
   //                                 Inverse(MatS6(" 1 0 0 0 1 0   0 1 0 0 -1 0   0 0 1 0 1 0   0 0 0 0 1 1   0 0 0 0 -1 0   0 0 0 1 1 0"))));  // m or t
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s5 + s1;
   ss2 = -s5 + s2;
   ss3 = s5 + s3;
   ss4 = s5 + s6;
   ss5 = -s5;
   ss6 = s5 + s4;
   return d;
}

S6 S6Dist::Reduce61(const S6& din) {
   // reduce scale 6 non-zero
//   vRed.push_back(std::make_pair(Inverse(MatS6(" 0 1 0 0 0 1   1 0 0 0 0 1   0 0 1 0 0 -1   0 0 0 1 0 1   0 0 0 0 1 1   0 0 0 0 0 -1")),
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s6 + s2;
   ss2 = s6 + s1;
   ss3 = -s6 + s3;
   ss4 = s6 + s4;
   ss5 = s6 + s5;
   ss6 = -s6;
   return d;
}

S6 S6Dist::Reduce62(const S6& din) {
   // reduce scale 6 non-zero
   //                                 Inverse(MatS6(" 1 0 0 0 0 1   0 1 0 0 0 1   0 0 1 0 0 -1   0 0 0 0 1 1   0 0 0 1 0 1   0 0 0 0 0 -1"))));  // n or u
   S6 d(din);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s6 + s1;
   ss2 = s6 + s2;
   ss3 = -s6 + s3;
   ss4 = s6 + s5;
   ss5 = s6 + s4;
   ss6 = -s6;
   return d;
}

S6 S6Dist::Unreduce11(const S6& din) {
   // For unreducing scalar 11
   // MatS6(�-1 0 0 0 0 0    1 1 0 0 0 0    1 0 0 0 1 0    -1 0 0 1 0 0    1 0 1 0 0 0    1 0 0 0 0 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s1;
   ss2 = s1 + s2;
   ss3 = s1 + s5;
   ss4 = -s1 + s4;
   ss5 = s1 + s3;
   ss6 = s1 + s6;
   return d;
}

S6 S6Dist::Unreduce12(const S6& din) {
   // For unreducing scalar 12
   // MatS6(�-1 0 0 0 0 0    1 0 0 0 0 1    1 0 1 0 0 0    -1 0 0 1 0 0    1 0 0 0 1 0    1 1 0 0 0 0�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s1;
   ss2 = s1 + s6;
   ss3 = s1 + s3;
   ss4 = -s1 + s4;
   ss5 = s1 + s5;
   ss6 = s1 + s2;
   return d;
}

S6 S6Dist::Unreduce21(const S6& din) {
   // For unreducing scalar 21
   // MatS6(�1 1 0 0 0 0    0 -1 0 0 0 0    0 1 0 1 0 0    0 1 1 0 0 0    0 -1 0 0 1 0    0 1 0 0 0 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s2 + s1;
   ss2 = -s2;
   ss3 = s2 + s4;
   ss4 = s2 + s3;
   ss5 = -s2 + s5;
   ss6 = s2 + s6;
   return d;
}

S6 S6Dist::Unreduce22(const S6& din) {
   // For unreducing scalar 22
   // MatS6(�0 1 0 0 0 1    0 -1 0 0 0 0    0 1 1 0 0 0    0 1 0 1 0 0    0 -1 0 0 1 0    1 1 0 0 0 0�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s2 + s6;
   ss2 = -s2;
   ss3 = s2 + s3;
   ss4 = s2 + s4;
   ss5 = -s2 + s5;
   ss6 = s2 + s1;
   return d;
}

S6 S6Dist::Unreduce31(const S6& din) {
   // For unreducing scalar 31
   // MatS6(�1 0 1 0 0 0    0 0 1 1 0 0    0 0 -1 0 0 0    0 1 1 0 0 0    0 0 1 0 1 0    0 0 -1 0 0 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s3 + s1;
   ss2 = s3 + s4;
   ss3 = -s3;
   ss4 = s3 + s2;
   ss5 = s3 + s5;
   ss6 = -s3 + s6;
   return d;
}

S6 S6Dist::Unreduce32(const S6& din) {
   // For unreducing scalar 32
   // MatS6(�0 0 1 0 1 0    0 1 1 0 0 0    0 0 -1 0 0 0    0 0 1 1 0 0    1 0 1 0 0 0    0 0 -1 0 0 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s3 + s5;
   ss2 = s3 + s2;
   ss3 = -s3;
   ss4 = s3 + s4;
   ss5 = s3 + s1;
   ss6 = -s3 + s6;
   return d;
}

S6 S6Dist::Unreduce41(const S6& din) {
   // For unreducing scalar 41
   // MatS6(�1 0 0 -1 0 0    0 0 1 1 0 0    0 1 0 1 0 0    0 0 0 -1 0 0    0 0 0 1 1 0    0 0 0 1 0 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s4 + s1;
   ss2 = s4 + s3;
   ss3 = s4 + s2;
   ss4 = -s4;
   ss5 = s4 + s5;
   ss6 = s4 + s6;
   return d;
}

S6 S6Dist::Unreduce42(const S6& din) {
   // For unreducing scalar 42
   // MatS6(�1 0 0 -1 0 0    0 1 0 1 0 0    0 0 1 1 0 0    0 0 0 -1 0 0    0 0 0 1 0 1    0 0 0 1 1 0�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = -s4 + s1;
   ss2 = s4 + s2;
   ss3 = s4 + s3;
   ss4 = -s4;
   ss5 = s4 + s6;
   ss6 = s4 + s5;
   return d;
}

S6 S6Dist::Unreduce51(const S6& din) {
   // For unreducing scalar 51
   // MatS6(�0 0 1 0 1 0    0 1 0 0 -1 0    1 0 0 0 1 0    0 0 0 1 1 0    0 0 0 0 -1 0    0 0 0 0 1 1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s5 + s3;
   ss2 = -s5 + s2;
   ss3 = s5 + s1;
   ss4 = s5 + s4;
   ss5 = -s5;
   ss6 = s5 + s6;
   return d;
}

S6 S6Dist::Unreduce52(const S6& din) {
   // For unreducing scalar 52
   // MatS6(�1 0 0 0 1 0    0 1 0 0 -1 0    0 0 1 0 1 0    0 0 0 0 1 1    0 0 0 0 -1 0    0 0 0 1 1 0�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s5 + s1;
   ss2 = -s5 + s2;
   ss3 = s5 + s3;
   ss4 = s5 + s6;
   ss5 = -s5;
   ss6 = s5 + s4;
   return d;
}

S6 S6Dist::Unreduce61(const S6& din) {
   // For unreducing scalar 61
   // MatS6(�0 1 0 0 0 1    1 0 0 0 0 1    0 0 1 0 0 -1    0 0 0 1 0 1    0 0 0 0 1 1    0 0 0 0 0 -1�);
   S6 d;
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s6 + s2;
   ss2 = s6 + s1;
   ss3 = -s6 + s3;
   ss4 = s6 + s4;
   ss5 = s6 + s5;
   ss6 = -s6;
   return d;
}

S6 S6Dist::Unreduce62(const S6& din) {
   S6 d;
   // For unreducing scalar 62
   // MatS6(�1 0 0 0 0 1    0 1 0 0 0 1    0 0 1 0 0 -1    0 0 0 0 1 1    0 0 0 1 0 1    0 0 0 0 0 -1�);
   const double& s1 = din[0];
   const double& s2 = din[1];
   const double& s3 = din[2];
   const double& s4 = din[3];
   const double& s5 = din[4];
   const double& s6 = din[5];
   double& ss1 = d[0];
   double& ss2 = d[1];
   double& ss3 = d[2];
   double& ss4 = d[3];
   double& ss5 = d[4];
   double& ss6 = d[5];
   ss1 = s6 + s1;
   ss2 = s6 + s2;
   ss3 = -s6 + s3;
   ss4 = s6 + s5;
   ss5 = s6 + s4;
   ss6 = -s6;
   return d;
}
