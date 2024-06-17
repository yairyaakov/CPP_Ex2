//ID : 207723198
//Mail : yair852258@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <limits>

namespace ariel
{
    class Algorithms {
	private:
		static void dfs(const Graph &graph, vector<bool> &visited, size_t current_node);
		static string bfs(const Graph &graph, size_t start, size_t end);
 		static string BellmanFord(const Graph &graph, size_t start, size_t end);
        static string Dijkstra(const Graph &graph, size_t start, size_t end);
        static bool dfsCycleHelper(const vector<vector<int>> &adjMatrix, size_t node, int parentNode, vector<bool> &visited, vector<bool> &detectBackEdges, vector<size_t> &cyclePath);
		static string formatCyclePath(const vector<size_t> &pathCycle);

	public:
        // Check if the graph is connected
        static bool isConnected(const Graph& graph);

		// Find the shortest path between two vertices
		static string shortestPath(const Graph& graph, int start, int end);

        // Check if the graph contains a cycle
		static string isContainsCycle(const Graph &graph);

        // Check if the graph is bipartite
		static string isBipartite(const Graph &graph);

        // Check if the graph has a negative cycle
		static string negativeCycle(const Graph& graph);
    };
}
#endif /* ALGORITHMS_HPP */