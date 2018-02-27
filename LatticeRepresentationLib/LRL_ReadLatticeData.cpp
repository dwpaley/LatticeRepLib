
#include "stdafx.h"

#include "LRL_Cell.h"
#include "G6.h"
#include "S6.h"
#include "B4.h"
#include "D7.h"
#include "GenerateRandomLattice.h"
#include "LRL_RandTools.h"
#include "LRL_ReadLatticeData.h"
#include "LRL_StringTools.h"
#include "LRL_ToString.h"
#include "LRL_StringTools.h"


#include <algorithm>
#include <complex>
#include <cmath>
#include <sstream>
#include <string>
#include <utility>

void LRL_ReadLatticeData::CellReader(const std::string& lattice, const std::string& cell) {
   CellReader(lattice + " " + cell);
}

static int folseed = 19192;
static GenerateRandomLattice<S6> generator(folseed);

void LRL_ReadLatticeData::CellReader(const std::string& s) {
   if ((LRL_StringTools::strToupper(s.substr(0, 3)) != std::string("END"))) {
      std::istringstream iss(s);
      iss >> m_inputDataType;
      if (LRL_StringTools::strToupper(m_inputDataType) == "RANDOM") {
         m_inputDataType = "P";
         m_lattice = "P";
         //const G6 g6Cell = LRL_Cell::randDeloneUnreduced();
         const G6 g6Cell = generator.SetLengthLimits(10.0, 100.0).Generate();
         m_cell = LRL_Cell(g6Cell);
         m_strCell = LRL_ToString(LRL_Cell(m_cell));
      }
      else if (toupper(m_inputDataType[0]) == 'V' ||toupper(m_inputDataType[0]) == 'G') {
         G6 v6;
         for (unsigned long i = 0; i < 6; ++i)
            iss >> v6[i];
         m_cell = v6;
      }
      else if (toupper(m_inputDataType[0]) == 'D') {
         D7 v7;
         double d;
         for (unsigned long i = 0; i < 7; ++i) {
            iss >> d;
            v7[i] = d;
         }
         v7.SetValid(true);
         G6 v6(v7);
         m_cell = v6;
      }
      else if (toupper(m_inputDataType[0]) == 'S') {
         S6 e;
         for (unsigned long i = 0; i < 6; ++i)
            iss >> e[i];
         m_cell = e;
      }
      else if (LRL_StringTools::strToupper(m_inputDataType).substr(0, m_inputDataType.length()) == "C3") {
         C3 e;
         std::vector<double> vd(20);
         double d;
         for (unsigned long i = 0; i < 6; ++i) {
            iss >> d;
            vd[i] = d;
         }
         e[0] = std::complex<double>(vd[0], vd[1]);
         e[1] = std::complex<double>(vd[2], vd[3]);
         e[2] = std::complex<double>(vd[4], vd[5]);
         e.SetValid(true);
         m_lattice = "P";
         m_inputDataType = "P";
         m_cell = e;
      }
      else {
         for (unsigned long i = 0; i < 6; ++i)
            iss >> m_cell[i];
         for (unsigned long i = 3; i < 6; ++i)
            m_cell[i] *= 4.0 * atan(1.0) / 180.0;
      }
      iss >> m_lattice;
      m_lattice = m_inputDataType;
      m_cell.SetValid(true);
      if (LRL_StringTools::strToupper(m_lattice) == "END" || LRL_StringTools::strToupper(m_lattice) == "EOF") {
         m_lattice = "EOF";
         return;
      }
   }
   else {
      m_lattice = "EOF";
   }
}

LRL_ReadLatticeData::LRL_ReadLatticeData(const int seed /*= 0*/) {

   if (seed > 0) generator.SetSeed(seed);
}
LRL_ReadLatticeData LRL_ReadLatticeData::read(void) {
   std::getline(std::cin, m_strCell);
   if (std::cin && (LRL_StringTools::strToupper(m_strCell.substr(0, 3)) != std::string("END"))) {
      CellReader(m_strCell);
      return *this;
   }
   else {
      m_lattice = "EOF";
      return *this;
   }
}
