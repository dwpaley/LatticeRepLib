
#include <string>
#include <utility>
#include <vector>

#include "FollowerConstants.h"
#include <cfloat>

namespace {
   // cannot access outside this file
   std::string BASIC_COLORS[] = { "red", "lightblue", "turquoise", "slategrey", 
                     "orange", "blueviolet", "coral", "saddlebrown", "blue", "pink", "violet", 
                     "deeppink", "mediumvioletred", "tomato", "greenyellow", "olive" };
};

   FollowerConstants::enumFollowerMode FollowerConstants::globalFollowerMode = FollowerConstants::globalSinglePoint;

   bool FollowerConstants::globalPrintAllDistanceData = true;
   bool FollowerConstants::globalOutputGlitchesOnly   = false;

   double FollowerConstants::globalFractionalAmountToPerturb          = 0.05;
   double FollowerConstants::globalPercentChangeToDetect                = 3.0; // GLITCH DETECTION LEVEL - percent of deltas in either of the top two histogram bins
   double FollowerConstants::globalFractionToDetermineCloseToBoundary = 0.065;
   
   unsigned long FollowerConstants::globalStepsPerFrame           = 100;
   unsigned long FollowerConstants::globalNumberOfTrialsToAttempt = 20;  // applies when not in movie generation
   bool FollowerConstants::globalPlotAllSegmentsAsBlack  = true;

   std::string FollowerConstants::globalFileNamePrefix   = "Fol";
   bool FollowerConstants::NiggliSellingFirst = false;

   std::vector<std::string> FollowerConstants::globalDistanceEnableList{ "S6", "CS" };
   std::string globalDistanceDisable = "";

   double SVG_WriterConstants::globalGraphSpace  = 1000; // px
   double SVG_WriterConstants::globalGraphBorder = 100; // px
   double SVG_WriterConstants::globalPlotSpace   = SVG_WriterConstants::globalGraphSpace - 2*SVG_WriterConstants::globalGraphBorder;


   int SVG_DistancePlotConstants::globalDataAxisWidth       = 6; // px
   int SVG_DistancePlotConstants::globalY_AxisTicMarkLength = 20; // px
   int SVG_DistancePlotConstants::globalX_AxisTicMarkLength = SVG_DistancePlotConstants::globalY_AxisTicMarkLength; // px


   std::string GLOBAL_Report::globalDataReport = "";

   bool GLOBAL_RunInputVector::globalConstantRandomSeed = false;
   int GLOBAL_RunInputVector::globalInputRandomSeed = 19191;
   unsigned long GLOBAL_Files::globalCounter = 0;
   bool GLOBAL_Files::globalShouldTimeStamp = true;
