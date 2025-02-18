#ifndef MULTIFOLLOWER_H
#define MULTIFOLLOWER_H

#include <algorithm>
#include <ctime>
#include <list>
#include <set>
#include <utility>
#include <vector>

#include "CS6Dist.h"
#include "DC.h"
#include "D13.h"
#include "DistanceLineDescriptions.h"
#include "FollowerConstants.h"
#include "G6.h"
#include "LM.h"
#include "LRL_Path.h"
#include "LRL_MinMaxTools.h"
#include "S6.h"
#include "D7.h"
#include "OutlierFinder.h"


class MultiFollower {
public:
   MultiFollower(){}
   MultiFollower(const std::vector<std::pair<S6, S6> >& inputPath);

   LRL_Path<S6> GetS6( void ) const;
   LRL_Path<G6> GetG6( void ) const;
   LRL_Path<D7> GetD7( void ) const;
   LRL_Path<S6> GetCS( void ) const;
   LRL_Path<G6> GetV7( void ) const;
   LRL_Path<S6> GetLM(void) const;
   LRL_Path<DC> GetDC(void) const;
   LRL_Path<D13> GetD13(void) const;

   MultiFollower CalculateDistancesS6( const MultiFollower& mf ) const;
   MultiFollower CalculateDistancesG6( const MultiFollower& mf ) const;
   MultiFollower CalculateDistancesD7( const MultiFollower& mf ) const;
   MultiFollower CalculateDistancesCS( const MultiFollower& mf ) const;
   MultiFollower CalculateDistancesV7( const MultiFollower& mf ) const;
   MultiFollower CalculateDistancesLM(const MultiFollower& mf) const;
   MultiFollower CalculateDistancesDC(const MultiFollower& mf) const;
   MultiFollower CalculateDistancesD13(const MultiFollower& mf) const;
   MultiFollower GenerateAllDistances(void);
   void SetLatticePointChoiceForDistanceCalculation();

   void SetDistancesS6( const std::vector<double>& v ) { m_s6path.SetDistances( v ); }
   void SetDistancesG6( const std::vector<double>& v ) { m_g6path.SetDistances( v ); }
   void SetDistancesD7( const std::vector<double>& v ) { m_d7path.SetDistances( v ); }
   void SetDistancesCS( const std::vector<double>& v ) { m_cspath.SetDistances( v ); }
   void SetDistancesV7( const std::vector<double>& v ) { m_v7path.SetDistances( v ); }
   void SetDistancesLM(const std::vector<double>& v) { m_lmpath.SetDistances(v); }
   void SetDistancesDC(const std::vector<double>& v) { m_dcpath.SetDistances(v); }
   void SetDistancesD13(const std::vector<double>& v) { m_d13path.SetDistances(v); }

   LRL_Path<S6>& GetPathS6( void ) { return m_s6path; }
   LRL_Path<G6>& GetPathG6( void ) { return m_g6path; }
   LRL_Path<D7>& GetPathD7( void ) { return m_d7path; }
   LRL_Path<S6>& GetPathCS( void ) { return m_cspath; }
   LRL_Path<G6>& GetPathV7( void ) { return m_v7path; }
   LRL_Path<S6>& GetPathLM(void) { return m_lmpath; }
   LRL_Path<DC>& GetPathDC(void) { return m_dcpath; }
   LRL_Path<D13>& GetPathD13(void) { return m_d13path; }

   std::pair<double, double> GetMinMax(void) const;
   size_t size(void)const { return maxNC(m_s6path.size(), m_g6path.size(), m_d7path.size(), m_cspath.size()); }
   const double GetTime2ComputerFrame(void) const;
   void SetTime2ComputeFrame(const double computeTime);
   DistanceLineDescriptions GetLineDescriptions(void) const { return m_lineDescription; }
   void SetComputeStartTime(void) { m_ComputeStartTime = std::clock(); }
   double GetTime2ComputeFrame(void) const { return m_seconds2ComputerFrame; }
   std::clock_t GetComputeStartTime(void) const {return m_ComputeStartTime; }

   std::set<size_t> DetermineOutliers(const std::vector<double> distanceList) const;
   const std::set<size_t> DetermineIfSomeDeltaIsTooLarge(const std::vector<double>& distances) const;
   bool HasGlitches(void) const;
   void SetComputeTime(const std::string& name, const double time);

private:
   LRL_Path<S6> m_s6path;
   LRL_Path<G6> m_g6path;
   LRL_Path<D7> m_d7path;
   LRL_Path<S6> m_cspath;
   LRL_Path<G6> m_v7path;
   LRL_Path<S6> m_lmpath;
   LRL_Path<DC> m_dcpath;
   LRL_Path<D13> m_d13path;

   enum m_enumLatticePointChoiceForDistanceCalculation {versusFirstPoint, versusCorrespondingPoint};
   m_enumLatticePointChoiceForDistanceCalculation m_latticePointChoiceForDistanceCalculation;
   std::clock_t m_ComputeStartTime;
   double m_seconds2ComputerFrame;
   std::set<size_t> m_glitches;
   DistanceLineDescriptions m_lineDescription;

   template<typename T_OUTPUT, typename T_RESULT, typename TREDUCE>
   T_RESULT Converter(const std::vector<std::pair<S6, S6> >& s6path) {
      std::vector<std::pair<T_OUTPUT, T_OUTPUT> > result;
      for (size_t i = 0; i < s6path.size(); ++i) {
         const std::pair<S6, S6> p(s6path[i]);
         G6 reduced;
         const bool b = TREDUCE::Reduce(G6(p.second), reduced);
         const T_OUTPUT out(reduced);
         result.push_back(std::make_pair(T_OUTPUT(s6path[i].first), out));
      }
      return result;
   }

   template<typename TVEC>
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   const std::vector<size_t> DetermineIfSomeDeltaIsTooLarge(const LRL_Path<TVEC>& path) {
      return(DetermineIfSomeDeltaIsTooLarge(path.GetDistances()));
   }

};

#endif // MULTIFOLLOWER_H

