//ID : 207723198
//Mail : yair852258@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include "GraphOperators.hpp"
#include <sstream>

using namespace std;
TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(matrix);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 + g2;

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};

    expectedGraph.loadGraph(expected);
    CHECK(g3 == expectedGraph);
}

TEST_CASE("Test graph sub")
{
    ariel::Graph g1;
    vector<vector<int>> matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(matrix);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 - g2;

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    expectedGraph.loadGraph(expected);

    ariel::Graph g5;
    vector<vector<int>> weightedGraph1 = {
        {0, 2, 2, 1},
        {1, 0, 5, 0},
        {-1, 1, 0, 5},
         {1, 0, 2, 0}};
    g5.loadGraph(weightedGraph1);

    ariel::Graph g6;
    vector<vector<int>> weightedGraphh = {
        {0, 2, 1, -1},
        {2, 0, 1, 0},
        {3, 1, 0, 1},
        {1, 0, 2, 0}};
    g6.loadGraph(weightedGraphh);

    ariel::Graph g7 = g5 - g6;

    ariel::Graph expectedGraph2;
    vector<vector<int>> expected2 = {
       {0, 0, 1, 2},
        {-1, 0, 4, 0},
        {-4, 0, 0, 4},
        {0, 0, 0, 0}};
     expectedGraph2.loadGraph(expected2);

    CHECK(g3 == expectedGraph);
    CHECK(g7 == expectedGraph2);
}

TEST_CASE("Test graph addition assignment")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 1, 0, 3},
        {1, 0, 1, 4},
        {0, 1, 0, 2},
        {3, 4, 2, 0}
    };
    g1.loadGraph(matrix1);

    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 2, 1, 0},
        {2, 0, 3, 1},
        {1, 3, 0, 4},
        {0, 1, 4, 0}
    };
    g2.loadGraph(matrix2);

    g1 += g2;

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, 3, 1, 3},
        {3, 0, 4, 5},
        {1, 4, 0, 6},
        {3, 5, 6, 0}
        };
    expectedGraph.loadGraph(expected);

    CHECK(g1==expectedGraph);
}

TEST_CASE("Test graph subtraction assignment")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 3, 1, 3},
        {3, 0, 4, 5},
        {1, 4, 0, 6},
        {3, 5, 6, 0}
    };
    g1.loadGraph(matrix1);

    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 2, 1, 0},
        {2, 0, 3, 1},
        {1, 3, 0, 4},
        {0, 1, 4, 0}
    };
    g2.loadGraph(matrix2);

    g1 -= g2;

    ariel::Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, 1, 0, 3},
        {1, 0, 1, 4},
        {0, 1, 0, 2},
        {3, 4, 2, 0}
    };
    g3.loadGraph(expectedGraph);

    CHECK(g1==g3);
}

TEST_CASE("Test unary plus operator")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 1, 0, 3},
        {1, 0, 1, 4},
        {0, 1, 0, 2},
        {3, 4, 2, 0}
    };
    g1.loadGraph(matrix1);

    ariel::Graph g2 = +g1;

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, 1, 0, 3},
        {1, 0, 1, 4},
        {0, 1, 0, 2},
        {3, 4, 2, 0}
    };
    expectedGraph.loadGraph(expected);

    CHECK(g2==expectedGraph);
}

TEST_CASE("Test unary minus operator")
{
    ariel::Graph g1;
    vector<vector<int>> matrix = {
        {0, 1, 0, 3},
        {1, 0, 1, 4},
        {0, 1, 0, -2},
        {3, 4, 2, 0}
    };
    g1.loadGraph(matrix);

    ariel::Graph g2 = -g1;

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, -1, 0, -3},
        {-1, 0, -1, -4},
        {0, -1, 0, 2},
        {-3, -4, -2, 0}
    };
    expectedGraph.loadGraph(expected);

    CHECK(g2==expectedGraph);
}

TEST_CASE("Larger graph with sub-matrix relationship")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
       {0, 2, 3},
       {1, 0, 3},
       {4, 5, 0}
  };
  g1.loadGraph(matrix1);

  ariel::Graph g2;
  vector<vector<int>> matrix2 ={
    {0 , 2},
    {1 , 0}};
  g2.loadGraph(matrix2);

  REQUIRE(g1 > g2);
}

TEST_CASE("Test < that no sub matrix")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0}
    };
    g1.loadGraph(matrix1);

    //Graph g3 is not containd in graph g2 - therefor the inequality will determine by number of edges
    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 1, 0, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 0, 0}
    };
    g2.loadGraph(matrix2);
    REQUIRE(g1 > g2);
    REQUIRE(g1 >= g2);

    // Graph g3 is not containd in graph g2 and thay have the same number of edges - therefor the inequality will determine by number of vertices
    ariel::Graph g3;
    vector<vector<int>> matrix3 = {
      {0, 1, 0},
      {1, 0, 1},
      {0, 1, 0}
    };
    g3.loadGraph(matrix3);
    REQUIRE(g2 > g3);
}

TEST_CASE("Smaller graph is not greater")
{
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 2},
        {1, 0}};
    g1.loadGraph(matrix1);

    ariel::Graph g2;
    vector<vector<int>> matrix2 ={
      {0, 2, 3},
      {1, 0, 3},
      {4, 5, 0}};
    g2.loadGraph(matrix2);

    REQUIRE(!(g1 > g2));
    REQUIRE(!(g1 >= g2));
    REQUIRE(g1 < g2); // g2 is bigger matrix then g1
    REQUIRE(g1 <= g2);
}

TEST_CASE("Smaller graph is not greater")
{
ariel::Graph g1;
vector<vector<int>> matrix1 = {
  {0, 2, 3, 4, 5},
  {1, 0, 3, 4, 5},
  {4, 5, 0, 3, 5},
  {4, 5, 0, 0, 0},
  {1, 5, 2, 0, 0}};
  g1.loadGraph(matrix1);

  ariel::Graph g2;
  vector<vector<int>> matrix2 = {
        {0, 3},
        {5, 0}};
  g2.loadGraph(matrix2);

  CHECK(g1 > g2);
  CHECK(g1 >= g2) ;
  CHECK_FALSE(g1 < g2);
  CHECK_FALSE(g1 <= g2);
}

TEST_CASE("Test pre-increment and post-increment operators") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ++g1;

    ariel::Graph expectedGraph1;
    vector<vector<int>> expected1 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}
    };
    expectedGraph1.loadGraph(expected1);

    CHECK(g1 == expectedGraph1);

    g1++;

    ariel::Graph g3;
    vector<vector<int>> expectedGraph2 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}
    };
    g3.loadGraph(expectedGraph2);

    CHECK(g1 == g3);
    CHECK(g1 == g3++);
}

TEST_CASE("Test pre-decrement and post-decrement operators") {
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 3, 2},
        {3, 0, 3},
        {2, 3, 0}
    };
    g1.loadGraph(matrix1);

    --g1;
    ariel::Graph expectedGraph1;
    vector<vector<int>> expected1 = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}
    };
    expectedGraph1.loadGraph(expected1);

    CHECK(g1 == expectedGraph1);

    ariel::Graph notExpectedGraph;
    vector<std::vector<int>> notExpected = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    notExpectedGraph.loadGraph(notExpected);

    ariel::Graph expectedGraph2;
    vector<vector<int>> expected2 = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}
    };
    expectedGraph2.loadGraph(expected2);

    CHECK_FALSE(notExpectedGraph == g1--);
    CHECK(expectedGraph2 == g1--);
}

TEST_CASE("Test graph multiplication and output operator")
{
    stringstream ss;

    //Check multiplication and creating a new garph
    ariel::Graph g1;
    vector<vector<int>> matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(matrix);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 * g2;

    ss << g3;
    CHECK(ss.str() == "Graph with 3 vertices and 2 edges.\n[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]\n");

    ss.str("");

    ariel::Graph g4;
    vector<vector<int>> matrix2 = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}};
    g4.loadGraph(matrix2);

    ariel::Graph g5;
    vector<vector<int>> matrix3 = {
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(matrix3);

    ariel::Graph g6 = g4 * g5;

    ss << g6;
    CHECK(ss.str() == "Graph with 5 vertices and 20 edges.\n[0, 1, 1, 1, 1]\n[2, 0, 1, 2, 1]\n[1, 1, 0, 1, 1]\n[2, 1, 1, 0, 1]\n[1, 1, 1, 1, 0]\n");

    ss.str("");

    g4 *= g5;
    ss << g4;
    CHECK(ss.str() == "Graph with 5 vertices and 20 edges.\n[0, 1, 1, 1, 1]\n[2, 0, 1, 2, 1]\n[1, 1, 0, 1, 1]\n[2, 1, 1, 0, 1]\n[1, 1, 1, 1, 0]\n");

    ss.str("");

    //Check multiplication with a scalar and creating a new garph
    ariel::Graph g7 = g1*4;
    ss << g7;
    CHECK(ss.str() == "Graph with 3 vertices and 4 edges.\n[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]\n");

    ss.str("");

    //Check multiplication with a scalar to an already existing graph
    g1 *= 4;
    ss << g1;
    CHECK(ss.str() == "Graph with 3 vertices and 4 edges.\n[0, 4, 0]\n[4, 0, 4]\n[0, 4, 0]\n");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}



























