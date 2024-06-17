//ID : 207723198
//Mail : yair852258@gmail.com
#include "Graph.hpp"
#include "GraphOperators.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel
{
    //empty constructor
    Graph::Graph()
    {

    }

    //loading the graph
    void Graph::loadGraph(const vector<vector<int>>& adjMatrix)
    {
        // Check if the input matrix is a valid adjacency matrix
        if (adjMatrix.empty() || adjMatrix[0].empty())
        {
            throw std::invalid_argument("Invalid graph: The graph matrix is empty.");
        }

        // Check if the input matrix is a vsquare matrix
        size_t rows = adjMatrix.size();
        size_t columns = adjMatrix[0].size();
        if (rows != columns) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Check if diagonal elements are all zero
        for (size_t i = 0; i < adjMatrix.size(); ++i)
        {
            if (adjMatrix[i][i] != 0)
            {
                throw std::invalid_argument("Invalid graph: Diagonal elements must be zero.");
            }
        }

        // Load the graph from the input matrix
        this->adjacencyMatrix = adjMatrix;
    }

    //get the adj matrix that represnting the graph
    const vector<vector<int>>& Graph::getGraph() const
    {
        return adjacencyMatrix;
    }

	bool Graph::isDirected() const
    {
        // Checks if the graph matrix represents a directed graph
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); ++j)
            {
                if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
                {
                    return true; //If there is an edge from i to j but not from j to i this is mean that the graph is directed
                }
            }
        }
        return false; // If there are no differing edges, the graph is undirected
    }

    // Checks if the graph is weighted and if contains negative edges
	int Graph::isWeighted() const
    {
        for (const vector<int> &row : adjacencyMatrix)
        {
            for (int element : row)
            {
                if (element < 0)
                {
                    return -1; // The graph contains negative edges
                }
                if (element != 0 && element != 1)
                {
                    return 1; // The graph is weighted
                }
            }
        }
        return 0; // The graph is unweighted and contains no negative edges
    }

    void Graph:: printGraph() const
    {
		std::cout << "Graph with " << adjacencyMatrix.size() << " vertices and " << countEdges() << " edges." << std::endl;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            cout << "Adjacency list of vertex " << i << ": ";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0) // Only print non-zero edges cause if edge = 0 there is no edge
                {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

	int Graph::countEdges() const
    {
        int edge_counter = 0;
		bool graphIsDirected = isDirected();
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); ++j)
            {
                // For directed graph, count only if there's an edge from i to j
                // For undirected graph, count if there's any edge between i and j
                if ((adjacencyMatrix[i][j] > 0) && (!graphIsDirected || (graphIsDirected && adjacencyMatrix[j][i] > 0)))
                {
                    edge_counter++;
                }
            }
        }

        return edge_counter;
    }

    //get the adj matrix that represnting the graph
    size_t Graph::getNumVertices() const
    {
        return adjacencyMatrix.size();
    }

    // return g[index] : private function!  //two versions of operator[]
    const vector<int> &Graph::operator[](size_t index) const
    {
        return this->adjacencyMatrix[index];
    }

    vector<int> &Graph::operator[](size_t index)
    {
        return this->adjacencyMatrix[index];
    }

    // += operator
    Graph &Graph::operator+=(const Graph &other)
    {
        *this = *this + other;
        return *this;
    }

    // -= operator
    Graph &Graph::operator-=(const Graph &other)
    {
        *this = *this - other;
        return *this;
    }

    // + unary operator
    Graph Graph::operator+()
    {
        return *this;
    }

    // - unary operator
    Graph Graph::operator-()
    {
        // Negate all the weights in the graph
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); ++j)
            {
                (*this)[i][j] = -(*this)[i][j];
            }
        }
        return *this;
    }

    // ++ prefix operator
    Graph& Graph::operator++()
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); j++)
            {
                if(i != j && (*this)[i][j] != 0)
                {
                    ++(*this)[i][j];
                }
            }
        }
        return *this;
    }

    // ++ postfix operator
    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    // -- prefix operator
    Graph& Graph::operator--()
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); j++)
            {
                if(i != j && (*this)[i][j] != 0)
                {
                    --(*this)[i][j];
                }
            }
        }
        return *this;
    }

    // -- postfix operator
    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // this*=scalar
    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix.size(); j++)
            {
                (*this)[i][j] *= scalar;
            }

        }
        return *this;
    }

    // this*=g2
    Graph &Graph::operator*=(const Graph &other)
    {
        if(this->getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("Graphs aren't the same size");
        }

        size_t numVertice = this->getNumVertices();

        //Initialization of matrix with the size of the input graphs
        vector<vector<int>> matrixResult(numVertice, vector<int>(adjacencyMatrix.size(), 0));

        for(size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                for (size_t k = 0; k < numVertice; k++)
                {
                    if(i != j)
                    {
                        matrixResult[i][j] += (*this)[i][k] * other[k][j];
                    }
                }
            }
        }
        this->loadGraph(matrixResult);
        return *this;
    }

     // * scalar operator
    Graph operator*(const Graph &graph1, int scalar)
    {
        size_t numVertice = graph1.getNumVertices();

        // Create a new graph to store the result
        Graph graphResult;

        // Resize the result matrix to match the size of the input graphs
        graphResult.adjacencyMatrix.resize(numVertice, vector<int>(numVertice, 0));

        for (size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                graphResult[i][j] = graph1[i][j] * scalar;
            }
        }
        return graphResult;
    }

    // * operator
    Graph operator*(const Graph &graph1, const Graph &graph2)
    {
        if(graph1.getNumVertices() != graph2.getNumVertices())
        {
            throw std::invalid_argument("Graphs aren't the same size");
        }

        size_t numVertice = graph1.getNumVertices();

        // Create a new graph to store the result
        Graph graphResult;

        // Resize the result matrix to match the size of the input graphs
        graphResult.adjacencyMatrix.resize(numVertice, vector<int>(numVertice, 0));

        for(size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                for (size_t k = 0; k < numVertice; k++)
                {
                    if(i != j)
                    {
                        graphResult[i][j] += graph1[i][k] * graph2[k][j];
                    }
                }
            }
        }
        return graphResult;
    }

    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        // Print the number of vertices and edges
        os << "Graph with " << graph.getNumVertices() << " vertices and " << graph.countEdges() << " edges." << std::endl;

        // Print the adjacency matrix
        for (size_t i = 0; i < graph.getNumVertices(); i++)
        {
            os << "[";
            for (size_t j = 0; j < graph.getNumVertices(); j++)
            {
                os << graph[i][j];
                if (j < graph.getNumVertices()-1)
                {
                    os << ", ";
                }
            }
            os << "]" << std::endl;
        }
        return os;
    }
};