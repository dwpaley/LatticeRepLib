#include "DeloneTypeList.h"

#include "MatG6.h"
#include "SanMatrix.h"

#include <sstream>

//const std::vector<std::pair<char, MatS6> > DeloneTypeList::m_ToPrimitive = DeloneTypeList::MakeUncenterMatrices();;
//const std::vector<std::pair<char, MatS6> > DeloneTypeList::m_ToCentered = DeloneTypeList::MakeCenteringMatrices();

std::vector<std::pair<std::string, std::string> > CreateBravaisTypeList() {
   std::vector<std::pair<std::string, std::string> > v;
   v.push_back(std::make_pair("C1", "cI"));
   v.push_back(std::make_pair("C3", "cF"));
   v.push_back(std::make_pair("C5", "cP"));
   v.push_back(std::make_pair("T1", "tI"));
   v.push_back(std::make_pair("T2", "tI"));
   v.push_back(std::make_pair("T5", "tP"));
   v.push_back(std::make_pair("R1", "rP"));
   v.push_back(std::make_pair("R3", "rP"));
   v.push_back(std::make_pair("O1A", "oF"));
   v.push_back(std::make_pair("O1B", "oI"));
   v.push_back(std::make_pair("O2", "oI"));
   v.push_back(std::make_pair("O3", "oI"));
   v.push_back(std::make_pair("O4", "oP"));
   v.push_back(std::make_pair("O5", "oP"));
   v.push_back(std::make_pair("M1A", "mC"));
   v.push_back(std::make_pair("M1B", "mC"));
   v.push_back(std::make_pair("M2A", "mC"));
   v.push_back(std::make_pair("M2B", "mC"));
   v.push_back(std::make_pair("M3", "mC"));
   v.push_back(std::make_pair("M4", "mP"));
   v.push_back(std::make_pair("A1", "aP"));
   v.push_back(std::make_pair("A2", "aP"));
   v.push_back(std::make_pair("A3", "aP"));
   v.push_back(std::make_pair("H4", "hP"));
   return v;
}

std::vector<std::pair<std::string, std::string> > CreateCharacterList() {
   std::vector<std::pair<std::string, std::string> > v;
   v.push_back(std::make_pair("C1", "rrr rrr"));
   v.push_back(std::make_pair("C3", "rr0 rr0"));
   v.push_back(std::make_pair("C5", "000 rrr"));
   v.push_back(std::make_pair("T1", "rrs rrs"));
   v.push_back(std::make_pair("T2", "rr0 rrs"));
   v.push_back(std::make_pair("T5", "000 rrs"));
   v.push_back(std::make_pair("R1", "rrr sss"));
   v.push_back(std::make_pair("R3", "r0r sr0"));
   v.push_back(std::make_pair("O1A", "rrs rrt"));
   v.push_back(std::make_pair("O1B", "rrs rrs"));
   v.push_back(std::make_pair("O2", "rs0 sr0"));
   v.push_back(std::make_pair("O3", "rs0 rs0"));
   v.push_back(std::make_pair("O4", "00r sst"));
   v.push_back(std::make_pair("O5", "000 rst"));
   v.push_back(std::make_pair("M1A", "rrs ttu"));
   v.push_back(std::make_pair("M1B", "rst rsu"));
   v.push_back(std::make_pair("M2A", "rs0 rst"));
   v.push_back(std::make_pair("M2B", "rs0 stu"));
   v.push_back(std::make_pair("M3", "rs0 ts0"));
   v.push_back(std::make_pair("M4", "00r stu"));
   v.push_back(std::make_pair("A1", "rst uvw"));
   v.push_back(std::make_pair("A2", "rs0 tuv"));
   v.push_back(std::make_pair("A3", "rs0 tu0"));
   v.push_back(std::make_pair("H4", "00r rrs"));
   return v;
}

std::vector<std::pair<std::string, std::string> > CreateE3CenteringMatrixList() {
   std::vector<std::pair<std::string, std::string> > v;
   v.push_back(std::make_pair("C1", "0 1 1  1 0 1  1 1 0"));
   v.push_back(std::make_pair("C3", "1 1 0 -1 1 0  1 1 2"));
   v.push_back(std::make_pair("C5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(std::make_pair("C5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("H4", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("R1", "1 -1 0  0 1 -1  1 1 1"));
   v.push_back(std::make_pair("R3", "1 0 0  0 0 1  1 3 2"));
   v.push_back(std::make_pair("T1", "0 1 1  1 0 1  1 1 0"));
   v.push_back(std::make_pair("T2", "1 0 0  0 1 0  1 1 2"));
   v.push_back(std::make_pair("T5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("T5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(std::make_pair("T5", "0 1 0  0 1 1  1 0 0"));
   v.push_back(std::make_pair("O1A", "1 1 0 -1 1 0  1 1 2"));
   v.push_back(std::make_pair("O1B", "0 1 1  1 0 1  1 1 0"));
   v.push_back(std::make_pair("O2", "1 0 0  0 1 0  1 1 2"));
   v.push_back(std::make_pair("O3", "0 1 1  1 0 1  1 1 0"));
   v.push_back(std::make_pair("O3", "1 0 0  0 1 0  1 1 2"));
   v.push_back(std::make_pair("O4", "2 1 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("O4", "1 -1 0  1 1 0  0 0 1"));
   v.push_back(std::make_pair("O5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("O5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(std::make_pair("M1A", "-1 -1 -1  1 -1 0  0 0 1"));
   v.push_back(std::make_pair("M1B", "0 1 1  1 1 0 -1 0 -1"));
   v.push_back(std::make_pair("M2A", "-1 -1 -2 0 1 0  1 0 0"));
   v.push_back(std::make_pair("M2B", "0 1 1  1 1 0 -1 0 -1"));
   v.push_back(std::make_pair("M2B", "-1 -1 -1  1 -1 0  0 0 1"));
   v.push_back(std::make_pair("M3", "-1 -1 -2  0 1 0  1 0 0"));
   v.push_back(std::make_pair("M3", "1 1 0  0 -1 -1 -1 0 -1"));
   v.push_back(std::make_pair("M4", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("A1", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("A2", "1 0 0  0 1 0  0 0 1"));
   v.push_back(std::make_pair("A3", "1 0 0  0 1 0  0 0 1"));
   return v;
}


DeloneTypeList::DeloneTypeList()
   : m_types()
{
   //const std::vector<std::pair<std::string, MatS6> > toCentered = CreateListOfCenteringMatrices();
   const std::vector<std::pair< std::string, std::vector<MatS6> > > prjs;
   const std::vector<std::pair< std::string, std::vector<MatS6> > > perps;
   const std::vector<std::pair< std::string, std::vector<MatS6> > > toCanons;
   const std::vector<std::pair<std::string, std::string> > characters = CreateCharacterList();
   const std::vector<std::pair<std::string, std::string> > e3matrices = CreateE3CenteringMatrixList();
   const std::vector<std::pair<std::string, std::string> > bravaisLatticeTypes = CreateBravaisTypeList();


   if (/*(toCentered.size() != 24) || */(prjs.size() != 24) || (perps.size() != 24) || (toCanons.size() != 24)
      || (characters.size() != 24) || (e3matrices.size() != 24) || (bravaisLatticeTypes.size() != 24)) throw "wrong size";
   for (unsigned long i=0; i<24; ++i ) {
      //m_types.push_back(DeloneType(toCentered[i],prjs[i], perps[i], toCanons[i]));
   }
}

std::vector<std::pair<char, MatS6> > DeloneTypeList::MakeUncenterMatrices() {
   //if (m_ToPrimitive.empty()) {
   //   std::vector<std::pair<char, MatS6> >v;
   //   v.push_back(std::make_pair('P', MatG6::Eye()));
   //   v.push_back(std::make_pair('I', MatG6("1 0 0 0 0 0    0 1 0 0 0 0    .25 .25 .25 .25 .25 .25   0 1 0 .5 0 .5   1 0 0 0 .5 .5   0 0 0 0 0 1"))); // for monoclinic, assumes b unique
   //   v.push_back(std::make_pair('A', MatG6("1 0 0 0 0 0   0 1 0 0 0 0   0 .25 .25 .25 0 0    0 1 0 .5 0 0   0 0 0 0 .5 .5   0 0 0 0 0 1"))); // for monoclinic, assumes b unique
   //   v.push_back(std::make_pair('B', MatG6("1 0 0 0 0 0   0 1 0 0 0 0   .25 0 .25 0 .25 0   0 0 0 .5 0 .5   1 0 0 0 .5 0   0 0 0 0 0 1"))); // for monoclinic, assumes c unique
   //   v.push_back(std::make_pair('C', MatG6("1 0 0 0 0 0   .25 .25 0 0 0 .25   0 0 1 0 0 0    0 0 0 .5 .5 0   0 0 0 0 1 0   1 0 0 0 0 .5"))); // for monoclinic, assumes b unique
   //   v.push_back(std::make_pair('F', MatG6(".25 .25 0 0 0 .25     .25 0 .25 0 .25 0     0 .25 .25 .25  0 0    0 0 .5 .25 .25 .25     0 .5 0 .25 .25 .25     .5 0 0 .25 .25 .25")));
   //   v.push_back(std::make_pair('R', (1.0 / 9.0)* MatG6("1 1 1 1 -1 -1    4 1 1  1  2  2     1  4  1  -2  -1  2     -4  -4  2  -1  1  -5     2  -4  2  -1  -2  1     -4  2  2  2  1  1")));
   //   v.push_back(std::make_pair('H', MatG6::Eye()));
   //   return v;
   //}
   //else
   //return m_ToPrimitive;
   return std::vector<std::pair<char, MatS6> >();
}

MatS6 DeloneTypeList::MakeCentering(const MatS6& m) {
   const CMatrix cm(m);
   const CMatrix inv = cm.Inverse();
   const MatS6 m6(inv.GetVector());
   return m6;
}

std::vector<std::pair<char, MatS6> > DeloneTypeList::MakeCenteringMatrices() {
   if (m_types.empty()) MakeUncenterMatrices();

   std::vector<std::pair<char, MatS6> > v;
   //for ( unsigned long i=0; i< m_types.size(); ++i )
   //   v.push_back(std::make_pair(m_types[i].GetName(), MakeCentering(m_ToPrimitive[i].second)));
   throw;
   return v;
}

std::vector<std::pair<char, MatS6> > DeloneTypeList::GetMakePrimitiveMatrices() {
   //if (m_types.empty()) throw;
   //return m_ToPrimitive;
   throw;
   return std::vector<std::pair<char, MatS6> >();
}

std::vector<std::pair<char, MatS6> > DeloneTypeList::GetMakeCenteredMatrices() {
   //if (m_types.empty()) throw;
   //return m_ToCentered;
   throw;
   return std::vector<std::pair<char, MatS6> >();
}

MatS6 DeloneTypeList::findToPrimitive(const char c) const {
   //for (unsigned long i = 0; i < m_types.size(); ++i)
   //   if (c == m_types[i].first) return m_ToPrimitive[i].second;
   throw;
}

MatS6 DeloneTypeList::findToCentered(const char c) const {
   //for (unsigned long i = 0; i < m_types.size(); ++i)
   //   if (c == m_ToCentered[i].first) return m_ToCentered[i].second;
   throw;
}
MatS6 DeloneTypeList::findToPrimitive(const std::string& c) const {
   //for (unsigned long i = 0; i < m_types.size(); ++i)
   //   if (c[0] == m_ToPrimitive[i].first) return m_ToPrimitive[i].second;
   throw;
   return MatS6();
}

MatS6 DeloneTypeList::findToCentered(const std::string& c) const {
   //for (unsigned long i = 0; i < m_ToCentered.size(); ++i)
   //   if (c[0] == m_ToCentered[i].first) return m_ToCentered[i].second;
   throw;
}

std::vector<double> DeloneTypeList::Make3dVector( const std::string& s) {
   std::istringstream istr(s);
   double d;
   std::vector<double> v;
   while (istr && !istr.eof()) {
      istr >> d;
      v.push_back(d);
   }
   if (v.size() !=  9) throw;
   return v;
}



std::pair<std::string, MatS6 > DeloneTypeList::CreateCenteringMatrix(const std::string& lattice, const std::string& threespaceMatrix) {
   return std::make_pair(lattice, MatS6::e3Tos6(Make3dVector(threespaceMatrix)));
}

std::vector<std::pair<std::string, MatS6> > CreateListOfCenteringMatrices() {
   std::vector<std::pair<std::string, MatS6> > v;
   v.push_back(DeloneTypeList::CreateCenteringMatrix("C1", "0 1 1  1 0 1  1 1 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("C3", "1 1 0 -1 1 0  1 1 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("C5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("C5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("H4", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("R1", "1 -1 0  0 1 -1  1 1 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("R3", "1 0 0  0 0 1  1 3 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("T1", "0 1 1  1 0 1  1 1 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("T2", "1 0 0  0 1 0  1 1 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("T5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("T5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("T5", "0 1 0  0 1 1  1 0 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O1A", "1 1 0 -1 1 0  1 1 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O1B", "0 1 1  1 0 1  1 1 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O2", "1 0 0  0 1 0  1 1 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O3", "0 1 1  1 0 1  1 1 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O3", "1 0 0  0 1 0  1 1 2"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O4", "2 1 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O4", "1 -1 0  1 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O5", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("O5", "1 0 0  0 0 1  0 1 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M1A", "-1 -1 -1  1 -1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M1B", "0 1 1  1 1 0 -1 0 -1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M2A", "-1 -1 -2 0 1 0  1 0 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M2B", "0 1 1  1 1 0 -1 0 -1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M2B", "-1 -1 -1  1 -1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M3", "-1 -1 -2  0 1 0  1 0 0"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M3", "1 1 0  0 -1 -1 -1 0 -1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("M4", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("A1", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("A2", "1 0 0  0 1 0  0 0 1"));
   v.push_back(DeloneTypeList::CreateCenteringMatrix("A3", "1 0 0  0 1 0  0 0 1"));
   return v;
}

std::vector<std::pair<std::string,std::vector<double> > > DeloneTypeList::Make3dCenteringMatrices() {
   std::vector<std::pair<std::string, std::vector<double> > > v;
   v.push_back(std::make_pair("C1",  Make3dVector("0 1 1  1 0 1  1 1 0")));
   v.push_back(std::make_pair("C3",  Make3dVector("1 1 0 -1 1 0  1 1 2")));
   v.push_back(std::make_pair("C5",  Make3dVector("1 0 0  0 0 1  0 1 1")));
   v.push_back(std::make_pair("C5",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("H4",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("R1",  Make3dVector("1 -1 0  0 1 -1  1 1 1")));
   v.push_back(std::make_pair("R3",  Make3dVector("1 0 0  0 0 1  1 3 2")));
   v.push_back(std::make_pair("T1",  Make3dVector("0 1 1  1 0 1  1 1 0")));
   v.push_back(std::make_pair("T2",  Make3dVector("1 0 0  0 1 0  1 1 2")));
   v.push_back(std::make_pair("T5",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("T5",  Make3dVector("1 0 0  0 0 1  0 1 1")));
   v.push_back(std::make_pair("T5",  Make3dVector("0 1 0  0 1 1  1 0 0")));
   v.push_back(std::make_pair("O1A", Make3dVector("1 1 0 -1 1 0  1 1 2")));
   v.push_back(std::make_pair("O1B", Make3dVector("0 1 1  1 0 1  1 1 0")));
   v.push_back(std::make_pair("O2",  Make3dVector("1 0 0  0 1 0  1 1 2")));
   v.push_back(std::make_pair("O3",  Make3dVector("0 1 1  1 0 1  1 1 0")));
   v.push_back(std::make_pair("O3",  Make3dVector("1 0 0  0 1 0  1 1 2")));
   v.push_back(std::make_pair("O4",  Make3dVector("2 1 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("O4",  Make3dVector("1 -1 0  1 1 0  0 0 1")));
   v.push_back(std::make_pair("O5",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("O5",  Make3dVector("1 0 0  0 0 1  0 1 1")));
   v.push_back(std::make_pair("M1A", Make3dVector("-1 -1 -1  1 -1 0  0 0 1")));
   v.push_back(std::make_pair("M1B", Make3dVector("0 1 1  1 1 0 -1 0 -1")));
   v.push_back(std::make_pair("M2A", Make3dVector("-1 -1 -2 0 1 0  1 0 0")));
   v.push_back(std::make_pair("M2B", Make3dVector("0 1 1  1 1 0 -1 0 -1")));
   v.push_back(std::make_pair("M2B", Make3dVector("-1 -1 -1  1 -1 0  0 0 1")));
   v.push_back(std::make_pair("M3",  Make3dVector("-1 -1 -2  0 1 0  1 0 0")));
   v.push_back(std::make_pair("M3",  Make3dVector("1 1 0  0 -1 -1 -1 0 -1")));
   v.push_back(std::make_pair("M4",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("A1",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("A2",  Make3dVector("1 0 0  0 1 0  0 0 1")));
   v.push_back(std::make_pair("A3",  Make3dVector("1 0 0  0 1 0  0 0 1")));

   return v;
}

DeloneType DeloneTypeList::operator[] (const unsigned long n) {
   return m_types[n];
}

DeloneType DeloneTypeList::operator[] (const std::string& s) {
   for (unsigned long i = 0; i < m_types.size(); ++i)
      if (m_types[i].GetName() == s) return m_types[i];
   return DeloneType();
}