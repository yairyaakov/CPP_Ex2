//ID : 207723198
//Mail : yair852258@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

namespace ariel
{
    class Graph {
    private:
        vector<vector<int>> adjacencyMatrix; // Adjacency matrix

    public:
     	//empty constructor
        Graph();

		/**
         * Loads a graph from a given adjacency matrix.
         * @param matrix The adjacency matrix representing the graph.
         */
        void loadGraph(const vector<vector<int>>& adjacencyMatrix);

		/**
         * Gets the adjacency matrix of the graph.
         * @return The adjacency matrix.
         */
        const vector<vector<int>>& getGraph() const;

		/**
         * Checks if the graph is directed.
         * @return True if the graph is directed, false otherwise.
         */
        bool isDirected() const;

		/**
         * Checks if the graph is weighted.
         * @return 1 if the graph is weighted, 0 otherwise.
         */
        int isWeighted() const;

		/**
         * Prints the graph.
         */
        void printGraph() const;

		/**
         * Gets the number of Edges in the graph.
         * @return The number of Edges.
         */
		int countEdges() const;

		/**
         * Gets the number of vertices in the graph.
         * @return The number of vertices.
         */
        size_t getNumVertices() const;


        // [] operator for matrix - two vertions
        const vector<int>& operator[](size_t index) const;
        vector<int>& operator[](size_t index);

    	// += operator
    	Graph &operator+=(const Graph &other);

    	// -= operator
    	Graph &operator-=(const Graph &other);

    	// + unary operator
    	Graph operator+();

    	// - unary operator
    	Graph operator-();

    	// ++ prefix operator
    	Graph& operator++();

    	// ++ postfix operator
    	Graph operator++(int);

    	// -- prefix operator
    	Graph& operator--();

    	// -- postfix operator
    	Graph operator--(int);

    	// *= scalar operator
    	Graph& operator*=(int scalar);

    	// *= operator
    	Graph& operator*=(const Graph& graph2);

        // << operator
        friend ostream& operator<<(std::ostream& os, const Graph& g);
    };
}

#endif /* GRAPH_HPP */