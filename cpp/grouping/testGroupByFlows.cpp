#include <iostream>
#include <vector>
#include <set>
#include <memory>
using namespace std;

#include "CppUnitLite/TestHarness.h"
#include "grouping/groupByFlows.h"
using namespace groupsac::grouping;

//using namespace groupsac;
// |
// | :: estimators
// | :: ransac
// | :: grouping /!\ TODO

#include "armadillo/include/armadillo"
using namespace arma;
// |
// | :: mat
// | :: vec

//------------------------------
// Assert that test works
//------------------------------
TEST ( Group_by_Flows, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

//------------------------------
// Test : Ask one cluster
// - given a point cloud
// - ask for one cluster
// - assert that all point are assigned to the same cluster
// - check geometric center of the cluster
//------------------------------
TEST ( Group_by_Flows, TestOneCluster )
{
  mat xs1 = "1 2 3 4 5; 0 0 0 0 0";
  mat xs2 = "2 3 4 5 6; 0 0 0 0 0";
  double bandwidth = 10.0;
  int seg_num;
  mat vis_map, clustCent;
  CHECK( true == 
          groupByFlows(xs1, xs2, bandwidth, seg_num, vis_map, clustCent));

  // Check return values :
  CHECK( 1 == seg_num);

  mat expected_vis_map = "1; 1; 1; 1; 1";
  //TODO => CHECK( accu(vis_map == expected_vis_map) == expected_vis_map.n_elem );
  
  mat expected_clustCent = "3; 0; -1; 0"; // x, y, delta_x, delta_y
  CHECK( accu(clustCent == expected_clustCent) == expected_clustCent.n_elem );
}

//------------------------------
// Test : Ask two cluster
// - given a point cloud
// - ask for two cluster
// - assert that all points are assigned to the good cluster
// - check geometric center of the clusters
//------------------------------
TEST ( Group_by_Flows, TestTwoCluster )
{
  mat xs1 = " 1  2  3  4  5  6  7  8  9 10;0 0 0 0 0 0 0 0 0 0";
  mat xs2 = "11 12 13 14 15 -4 -3 -2 -1  0;0 0 0 0 0 0 0 0 0 0";
  double bandwidth = 10.0;
  int seg_num;
  mat vis_map, clustCent;
  CHECK( true == 
          groupByFlows(xs1, xs2, bandwidth, seg_num, vis_map, clustCent));

  // Check return values :
  CHECK( 2 == seg_num);

  mat expected_vis_map = "1 1 1 1 1 0 0 0 0 0; 0 0 0 0 0 1 1 1 1 1";
  vis_map = trans(vis_map);
  //TODO => CHECK( accu(vis_map == expected_vis_map) == expected_vis_map.n_elem );
  
//  mat expected_clustCent = "3 0 -10 0; 8 0 10 0"; // x, y, delta_x, delta_y
  mat expected_clustCent = "8 0 10 0; 3 0 -10 0"; // x, y, delta_x, delta_y
  expected_clustCent = trans(expected_clustCent);
  CHECK( accu(clustCent == expected_clustCent) == expected_clustCent.n_elem );
}

//------------------------------
// Test : Ask two cluster
// - given a point cloud
// - ask for two cluster
// - assert that all points are assigned to the good cluster
// - check geometric center of the c
//------------------------------
TEST ( Group_by_Flows, TestTwoCluster2 )
{
  mat xs1 = "1 2 3 4 5   6   7    8    9  10; 0 0 0 0 0 0 0 0 0 0";
  mat xs2 = "2 3 4 5 6 106 107  108  109 110; 0 0 0 0 0 0 0 0 0 0";
  double bandwidth = 10.0;
  int seg_num;
  mat vis_map, clustCent;
  CHECK( true == 
          groupByFlows(xs1, xs2, bandwidth, seg_num, vis_map, clustCent));

  // Check return values :
  CHECK( 2 == seg_num);

  mat expected_vis_map = "1 1 1 1 1 0 0 0 0 0; 0 0 0 0 0 1 1 1 1 1";
  vis_map = trans(vis_map);
  //TODO => CHECK( accu(vis_map == expected_vis_map) == expected_vis_map.n_elem );
  
  mat expected_clustCent = "8 0 -100 0; 3 0 -1 0"; // x, y, delta_x, delta_y
  expected_clustCent = trans(expected_clustCent);
  CHECK( accu(clustCent == expected_clustCent) == expected_clustCent.n_elem );
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */
