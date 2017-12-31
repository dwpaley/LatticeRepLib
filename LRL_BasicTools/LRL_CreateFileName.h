#ifndef LRL_CREATEFILENAME_H
#define LRL_CREATEFILENAME_H

#include <string>

class LRL_CreateFileName
{
public:
   static std::string Create( const std::string& prefix, const std::string& extension );
};


#endif  //  LRL_CREATEFILENAME_H
