#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "readGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
TEST_CASE("TESTING Read Graph")
{

    
  SECTION("reading graph 1")
    {
      ifstream fin;
      int** edgeList;
      string*vLabels;
      double* weights ;
      int numEdges;
      string*eLabels;
      int numVert = readGraph(fin,edgeList,weights,numEdges, vLabels, eLabels);
      REQUIRE(numVert == 4);
      REQUIRE_FALSE(numVert == 4);
    }
}

