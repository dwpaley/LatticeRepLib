
//#include "stdafx.h"


#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

#include "LRL_MaximaTools.h"

bool LRL_MaximaTools::not_space( const char c ) {
   return c != ' ';
}

bool LRL_MaximaTools::space( const char c ) {
   return c == ' ';
}

bool LRL_MaximaTools::newline( const char c ) {
   return c == '\n';
}

std::string LRL_MaximaTools::MaximaFromString( const std::string& s ) {
   std::string s_out;

   std::string::const_iterator it = s.begin( );
   while ( it != s.end( ) ) {
      // ignore leading blanks
      it = std::find_if( it, s.end( ), not_space );
      // find next end of word
      const std::string::const_iterator j = std::find_if( it, s.end( ), space );
      s_out += std::string( it, j );
      it = j;
      if ( std::find_if( it, s.end( ), not_space ) != s.end( ) ) s_out += ",";
   }
   return "[" + s_out + "]";
}

const std::string LRL_MaximaTools::Retrieve_One_Matrix_Row( const unsigned long rowLength, const std::string& s ) {
   unsigned int count = 0;

   std::string::const_iterator it = s.begin();
   while ( it != s.end( ) && count < rowLength ) {
      // ignore leading blanks and then find next end of word
      it = find_if( find_if( it, s.end( ), not_space ), s.end( ), space );
      ++count;
   }
   return std::string( s.begin( ), it );
}

std::string LRL_MaximaTools::MaximaFromString( const unsigned long rowLength, const std::string& s ) {
   unsigned long pos = 0;
   std::string sFrag;
   while ( pos < s.length( ) ) {
      const std::string nextFrag = Retrieve_One_Matrix_Row( rowLength, s.substr( pos, s.length( ) ) );
      if (nextFrag != "\n" && nextFrag != " \n") sFrag += MaximaFromString( nextFrag );
      pos += (unsigned long)(nextFrag.length( ));
      const std::string remaining = s.substr( pos, s.length() );
      if (remaining.find_first_not_of(" ") != std::string::npos)
         if (remaining != "\n" && remaining != " \n")sFrag += ",";
      else
         break;
   }

   for ( unsigned int i=0; i<sFrag.length(); ++i )
      if ( newline(sFrag[i] ) ) sFrag[i] = ' ';
   return  "[" +sFrag + "]";
}

//
//int main(int argc, char* argv[])
//{
//
//
//
//std::cout << std::endl << makMax( "P_NDaP1", "(1.0/7.0)",
//std::string( "6 -1 -1 -1 1 1 1    -1 6 -1 -1 1 1 1    -1 -1 6 -1 1 1 1    -1 -1 -1 6 1 1 1    1 1 1 1 6 -1 -1    1 1 1 1 -1 6 -1    1 1 1 1 -1 -1 6" ) );
//
//std::cout << std::endl << makMax( "P_NDaP2", "(1.0/12.0)",
//std::string( "8 0 -4 0 0 4 0    0 9 0 -3 3 0 3    -4 0 8 0 0 4 0    0 -3 0 9 3 0 3    0 3 0 3 9 0 -3    4 0 4 0 0 8 0    0 3 0 3 -3 0 9" ) );
//
//std::cout << std::endl << makMax( "P_NDaP3", "(1.0/10.0)",
//std::string( "6 1 -4 1 1 2 1    1 6 1 -4 1 2 1    -4 1 6 1 1 2 1    1 -4 1 6 1 2 1    1 1 1 1 6 2 -4    2 2 2 2 2 4 2    1 1 1 1 -4 2 6" ) );
//
//std::cout << std::endl << makMax( "P_NDrP1", "(1.0/21.0)",
//std::string( "4 4 4 -3 3 3 3    4 4 4 -3 3 3 3    4 4 4 -3 3 3 3    -3 -3 -3 18 3 3 3    3 3 3 3 4 4 4    3 3 3 3 4 4 4    3 3 3 3 4 4 4" ) );
//
//std::cout << std::endl << makMax( "P_NDrP2", "(1.0/8.0)",
//std::string( "3 -1 -2 2 -1 1 2    -1 1 2 0 1 1 0    -2 2 4 0 2 2 0    2 0 0 2 0 2 2    -1 1 2 0 1 1 0    1 1 2 2 1 3 2    2 0 0 2 0 2 2" ) );
//
//std::cout << std::endl << makMax( "P_NDhP", "(1.0/15.0)",
//std::string( "4 -1 -1 4 -1 3 4    -1 4 4 -1 4 3 -1    -1 4 4 -1 4 3 -1    4 -1 -1 4 -1 3 4    -1 4 4 -1 4 3 -1    3 3 3 3 3 6 3    4 -1 -1 4 -1 3 4" ) );
//
//std::cout << std::endl << makMax( "P_NDm1", "(1.0/14.0)",
//std::string( "5 -2 5 -2 2 2 2    -2 12 -2 -2 2 2 2    5 -2 5 -2 2 2 2    -2 -2 -2 12 2 2 2    2 2 2 2 5 -2 5    2 2 2 2 -2 12 -2    2 2 2 2 5 -2 5" ) );
//
//std::cout << std::endl << makMax( "P_NDm2", "(1.0/10.0)",
//std::string( "6 -2 1 -1 -1 1 4    -2 4 -2 2 2 -2 2    1 -2 6 -1 4 1 -1    -1 2 -1 6 1 4 1    -1 2 4 1 6 -1 1    1 -2 1 4 -1 6 -1    4 2 -1 1 1 -1 6" ) );
//
//std::cout << std::endl << makMax( "P_NDm3", "(1.0/6.0)",
//std::string( "4 0 -3 0 0 3 0    0 3 0 0 3 0 0    -3 0 4 0 0 3 0    0 0 0 3 0 0 3    0 3 0 0 3 0 0    3 0 3 0 0 4 0    0 0 0 3 0 0 3" ) );
//
//std::cout << std::endl << makMax( "P_NDm4", "(1.0/12.0)",
//std::string( "2 0 2 0 0 4 0    0 9 0 -3 3 0 3    2 0 2 0 0 4 0    0 -3 0 9 3 0 3    0 3 0 3 3 0 3    4 0 4 0 0 8 0    0 3 0 3 3 0 3" ) );
//
//std::cout << std::endl << makMax( "P_NDm5", "(1.0/20.0)",
//std::string( "7 7 -3 -3 2 4 2    7 7 -3 -3 2 4 2    -3 -3 7 7 2 4 2    -3 -3 7 7 2 4 2    2 2 2 2 12 4 -8    4 4 4 4 4 8 4    2 2 2 2 -8 4 12" ) );
//
//std::cout << std::endl << makMax( "P_NDm6", "(1.0/14.0)",
//std::string( "5 -2 5 -2 2 2 2    -2 5 -2 5 2 2 2    5 -2 5 -2 2 2 2    -2 5 -2 5 2 2 2    2 2 2 2 12 -2 -2    2 2 2 2 -2 12 -2    2 2 2 2 -2 -2 12" ) );
//
//std::cout << std::endl << makMax( "P_NDoP", "(1.0/8.0)",
//std::string( "3 -1 -1 1 -2 2 2    -1 3 -1 1 2 -2 2    -1 -1 3 1 2 2 -2    1 1 1 3 2 2 2    -2 2 2 2 4 0 0    2 -2 2 2 0 4 0    2 2 -2 2 0 0 4" ) );
//
//std::cout << std::endl << makMax( "P_NDoC", "(1.0/20.0)",
//std::string( "8 -4 -4 4 -4 4 4    -4 7 7 -2 2 3 3    -4 7 7 -2 2 3 3    4 -2 -2 12 8 2 2    -4 2 2 8 12 -2 -2    4 3 3 2 -2 7 7    4 3 3 2 -2 7 7" ) );
//
//std::cout << std::endl << makMax( "P_NDoI1", "(1.0/10.0)",
//std::string( "1 1 1 1 1 1 2    1 1 1 1 1 1 2    1 1 1 1 1 1 2    1 1 1 1 1 1 2    1 1 1 1 6 -4 2    1 1 1 1 -4 6 2    2 2 2 2 2 2 4" ) );
//
//std::cout << std::endl << makMax( "P_NDoI2", "(1.0/28.0)",
//std::string( "3 3 3 3 4 4 4    3 3 3 3 4 4 4    3 3 3 3 4 4 4    3 3 3 3 4 4 4    4 4 4 4 24 -4 -4    4 4 4 4 -4 24 -4    4 4 4 4 -4 -4 24" ) );
//
//std::cout << std::endl << makMax( "P_NDoI3", "(1.0/12.0)",
//std::string( "8 0 -4 0 0 4 0    0 3 0 3 3 0 3    -4 0 8 0 0 4 0    0 3 0 3 3 0 3    0 3 0 3 3 0 3    4 0 4 0 0 8 0    0 3 0 3 3 0 3" ) );
//
//std::cout << std::endl << makMax( "P_NDoF", "(1.0/14.0)",
//std::string( "5 -2 5 -2 2 2 2    -2 5 -2 5 2 2 2    5 -2 5 -2 2 2 2    -2 5 -2 5 2 2 2    2 2 2 2 5 -2 5    2 2 2 2 -2 12 -2    2 2 2 2 5 -2 5" ) );
//
//std::cout << std::endl << makMax( "P_NDtP", "(1.0/8.0)",
//std::string( "1 1 -1 1 0 0 2    1 1 -1 1 0 0 2    -1 -1 3 1 2 2 -2    1 1 1 3 2 2 2    0 0 2 2 2 2 0    0 0 2 2 2 2 0    2 2 -2 2 0 0 4" ) );
//
//std::cout << std::endl << makMax( "P_NDtI1", "(1.0/24.0)",
//std::string( "4 0 4 0 0 8 0    0 6 0 6 6 0 6    4 0 4 0 0 8 0    0 6 0 6 6 0 6    0 6 0 6 6 0 6    8 0 8 0 0 16 0    0 6 0 6 6 0 6" ) );
//
//std::cout << std::endl << makMax( "P_NDtI2", "(1.0/28.0)",
//std::string( "3 3 3 3 4 4 4    3 3 3 3 4 4 4    3 3 3 3 4 4 4    3 3 3 3 4 4 4    4 4 4 4 10 10 -4    4 4 4 4 10 10 -4    4 4 4 4 -4 -4 24" ) );
//
//std::cout << std::endl << makMax( "P_NDcP", "(1.0/24.0)",
//std::string( "1 1 1 3 2 2 2    1 1 1 3 2 2 2    1 1 1 3 2 2 2    3 3 3 9 6 6 6    2 2 2 6 4 4 4    2 2 2 6 4 4 4    2 2 2 6 4 4 4" ) );
//
//std::cout << std::endl << makMax( "P_NDcF", "(1.0/40.0)",
//std::string( "4 4 4 4 4 4 8    4 4 4 4 4 4 8    4 4 4 4 4 4 8    4 4 4 4 4 4 8    4 4 4 4 4 4 8    4 4 4 4 4 4 8    8 8 8 8 8 8 16" ) );
//
//std::cout << std::endl << makMax( "P_NDcI", "(1.0/84.0)",
//std::string( "9 9 9 9 12 12 12    9 9 9 9 12 12 12    9 9 9 9 12 12 12    9 9 9 9 12 12 12    12 12 12 12 16 16 16    12 12 12 12 16 16 16    12 12 12 12 16 16 16" ) );
//
//std::cout << std::endl;
//
/*
P_NDaP1, (1.0/7.0), [[6,-1,-1,-1,1,1,1],[-1,6,-1,-1,1,1,1],[-1,-1,6,-1,1,1,1],[-1,-1,-1,6,1,1,1],[1,1,1,1,6,-1,-1],[1,1,1,1,-1,6,-1],[1,1,1,1,-1,-1,6]]
P_NDaP2, (1.0/12.0), [[8,0,-4,0,0,4,0],[0,9,0,-3,3,0,3],[-4,0,8,0,0,4,0],[0,-3,0,9,3,0,3],[0,3,0,3,9,0,-3],[4,0,4,0,0,8,0],[0,3,0,3,-3,0,9]]
P_NDaP3, (1.0/10.0), [[6,1,-4,1,1,2,1],[1,6,1,-4,1,2,1],[-4,1,6,1,1,2,1],[1,-4,1,6,1,2,1],[1,1,1,1,6,2,-4],[2,2,2,2,2,4,2],[1,1,1,1,-4,2,6]]
P_NDrP1, (1.0/21.0), [[4,4,4,-3,3,3,3],[4,4,4,-3,3,3,3],[4,4,4,-3,3,3,3],[-3,-3,-3,18,3,3,3],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4]]
P_NDrP2, (1.0/8.0), [[3,-1,-2,2,-1,1,2],[-1,1,2,0,1,1,0],[-2,2,4,0,2,2,0],[2,0,0,2,0,2,2],[-1,1,2,0,1,1,0],[1,1,2,2,1,3,2],[2,0,0,2,0,2,2]]
P_NDhP, (1.0/15.0), [[4,-1,-1,4,-1,3,4],[-1,4,4,-1,4,3,-1],[-1,4,4,-1,4,3,-1],[4,-1,-1,4,-1,3,4],[-1,4,4,-1,4,3,-1],[3,3,3,3,3,6,3],[4,-1,-1,4,-1,3,4]]
P_NDm1, (1.0/14.0), [[5,-2,5,-2,2,2,2],[-2,12,-2,-2,2,2,2],[5,-2,5,-2,2,2,2],[-2,-2,-2,12,2,2,2],[2,2,2,2,5,-2,5],[2,2,2,2,-2,12,-2],[2,2,2,2,5,-2,5]]
P_NDm2, (1.0/10.0), [[6,-2,1,-1,-1,1,4],[-2,4,-2,2,2,-2,2],[1,-2,6,-1,4,1,-1],[-1,2,-1,6,1,4,1],[-1,2,4,1,6,-1,1],[1,-2,1,4,-1,6,-1],[4,2,-1,1,1,-1,6]]
P_NDm3, (1.0/6.0), [[4,0,-3,0,0,3,0],[0,3,0,0,3,0,0],[-3,0,4,0,0,3,0],[0,0,0,3,0,0,3],[0,3,0,0,3,0,0],[3,0,3,0,0,4,0],[0,0,0,3,0,0,3]]
P_NDm4, (1.0/12.0), [[2,0,2,0,0,4,0],[0,9,0,-3,3,0,3],[2,0,2,0,0,4,0],[0,-3,0,9,3,0,3],[0,3,0,3,3,0,3],[4,0,4,0,0,8,0],[0,3,0,3,3,0,3]]
P_NDm5, (1.0/20.0), [[7,7,-3,-3,2,4,2],[7,7,-3,-3,2,4,2],[-3,-3,7,7,2,4,2],[-3,-3,7,7,2,4,2],[2,2,2,2,12,4,-8],[4,4,4,4,4,8,4],[2,2,2,2,-8,4,12]]
P_NDm6, (1.0/14.0), [[5,-2,5,-2,2,2,2],[-2,5,-2,5,2,2,2],[5,-2,5,-2,2,2,2],[-2,5,-2,5,2,2,2],[2,2,2,2,12,-2,-2],[2,2,2,2,-2,12,-2],[2,2,2,2,-2,-2,12]]
P_NDoP, (1.0/8.0), [[3,-1,-1,1,-2,2,2],[-1,3,-1,1,2,-2,2],[-1,-1,3,1,2,2,-2],[1,1,1,3,2,2,2],[-2,2,2,2,4,0,0],[2,-2,2,2,0,4,0],[2,2,-2,2,0,0,4]]
P_NDoC, (1.0/20.0), [[8,-4,-4,4,-4,4,4],[-4,7,7,-2,2,3,3],[-4,7,7,-2,2,3,3],[4,-2,-2,12,8,2,2],[-4,2,2,8,12,-2,-2],[4,3,3,2,-2,7,7],[4,3,3,2,-2,7,7]]
P_NDoI1, (1.0/10.0), [[1,1,1,1,1,1,2],[1,1,1,1,1,1,2],[1,1,1,1,1,1,2],[1,1,1,1,1,1,2],[1,1,1,1,6,-4,2],[1,1,1,1,-4,6,2],[2,2,2,2,2,2,4]]
P_NDoI2, (1.0/28.0), [[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[4,4,4,4,24,-4,-4],[4,4,4,4,-4,24,-4],[4,4,4,4,-4,-4,24]]
P_NDoI3, (1.0/12.0), [[8,0,-4,0,0,4,0],[0,3,0,3,3,0,3],[-4,0,8,0,0,4,0],[0,3,0,3,3,0,3],[0,3,0,3,3,0,3],[4,0,4,0,0,8,0],[0,3,0,3,3,0,3]]
P_NDoF, (1.0/14.0), [[5,-2,5,-2,2,2,2],[-2,5,-2,5,2,2,2],[5,-2,5,-2,2,2,2],[-2,5,-2,5,2,2,2],[2,2,2,2,5,-2,5],[2,2,2,2,-2,12,-2],[2,2,2,2,5,-2,5]]
P_NDtP, (1.0/8.0), [[1,1,-1,1,0,0,2],[1,1,-1,1,0,0,2],[-1,-1,3,1,2,2,-2],[1,1,1,3,2,2,2],[0,0,2,2,2,2,0],[0,0,2,2,2,2,0],[2,2,-2,2,0,0,4]]
P_NDtI1, (1.0/24.0), [[4,0,4,0,0,8,0],[0,6,0,6,6,0,6],[4,0,4,0,0,8,0],[0,6,0,6,6,0,6],[0,6,0,6,6,0,6],[8,0,8,0,0,16,0],[0,6,0,6,6,0,6]]
P_NDtI2, (1.0/28.0), [[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[3,3,3,3,4,4,4],[4,4,4,4,10,10,-4],[4,4,4,4,10,10,-4],[4,4,4,4,-4,-4,24]]
P_NDcP, (1.0/24.0), [[1,1,1,3,2,2,2],[1,1,1,3,2,2,2],[1,1,1,3,2,2,2],[3,3,3,9,6,6,6],[2,2,2,6,4,4,4],[2,2,2,6,4,4,4],[2,2,2,6,4,4,4]]
P_NDcF, (1.0/40.0), [[4,4,4,4,4,4,8],[4,4,4,4,4,4,8],[4,4,4,4,4,4,8],[4,4,4,4,4,4,8],[4,4,4,4,4,4,8],[4,4,4,4,4,4,8],[8,8,8,8,8,8,16]]
P_NDcI, (1.0/84.0), [[9,9,9,9,12,12,12],[9,9,9,9,12,12,12],[9,9,9,9,12,12,12],[9,9,9,9,12,12,12],[12,12,12,12,16,16,16],[12,12,12,12,16,16,16],[12,12,12,12,16,16,16]]
*/

//	return 0;
//}

