//ID : 207723198
//Mail : yair852258@gmail.com

#include "GraphOperators.hpp"
#include "Graph.hpp"

namespace ariel {

    // + operator
    Graph operator+(const Graph &graph1, const Graph &graph2)
    {
        if(graph1.getNumVertices() != graph2.getNumVertices())
        {
            throw invalid_argument("Graphs aren't the same size");
        }

        // Create a new graph to store the result
        Graph graphResult;

        size_t numVertice = graph1.getNumVertices();

        vector<vector<int>> matrixResult(numVertice, vector<int>(numVertice, 0));

        for (size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                matrixResult[i][j] = graph1[i][j] + graph2[i][j];
            }
        }
        graphResult.loadGraph(matrixResult);
        return graphResult;
    }

    // - operator
    Graph operator-(const Graph &graph1, const Graph &graph2)
    {
        if(graph1.getNumVertices() != graph2.getNumVertices())
        {
            throw invalid_argument("Graphs aren't the same size");
        }

        // Create a new graph to store the result
        Graph graphResult;

        size_t numVertice = graph1.getNumVertices();

        vector<vector<int>> matrixResult(numVertice, vector<int>(numVertice, 0));

        for (size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                matrixResult[i][j] = graph1[i][j] - graph2[i][j];
            }
        }
        graphResult.loadGraph(matrixResult);
        return graphResult;
    }

    // > operator
    bool operator>(const Graph &graph1, const Graph &graph2)
    {
        if(graph1.getNumVertices() < graph2.getNumVertices())
        {
            return false;
        }

        //Chacks if graph 2 is contained in graph 1
        bool contains = true;
        for (size_t i = 0; i < graph2.getNumVertices(); i++)
        {
            for (size_t j = 0; j < graph2.getNumVertices(); j++)
            {
                if(graph2[i][j] != graph1[i][j])
                {
                    contains = false;
                }
            }
        }
        if(contains)
        {
            return graph1.getNumVertices() > graph2.getNumVertices();
        }

        // If graph 2 is not contained in graph 1 chacks by number of edges
        else
        {
            if(graph1.countEdges() > graph2.countEdges())
            {
                return true;
            }

            //Else chacks by number of vertices
            else
            {
                return graph1.getNumVertices() > graph2.getNumVertices();
            }
        }
    }

     // < operator
    bool operator<(const Graph &graph1, const Graph &graph2)
    {
        return graph2 > graph1;
    }

    // == operator
    bool operator==(const Graph &graph1, const Graph &graph2)
    {
        return !(graph1 > graph2) && !(graph2 > graph1);
    }

    // != operator
    bool operator!=(const Graph &graph1, const Graph &graph2)
    {
        return !(graph1 == graph2);
    }

    // >= operator
    bool operator>=(const Graph &graph1, const Graph &graph2)
    {
        return (graph1 > graph2) || (graph1 == graph2);
    }

    // <= operator
    bool operator<=(const Graph &graph1, const Graph &graph2)
    {
        return graph2 >= graph1;
    }

  // * scalar operator
    Graph operator*(const Graph &graph1, int scalar)
    {
        size_t numVertice = graph1.getNumVertices();

        // Create a new graph to store the result
        Graph graphResult;

        vector<vector<int>> matrixResult(numVertice, vector<int>(numVertice, 0));

        for (size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                matrixResult[i][j] = graph1[i][j] * scalar;
            }
        }
        graphResult.loadGraph(matrixResult);
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

        vector<vector<int>> matrixResult(numVertice, vector<int>(numVertice, 0));

        for(size_t i = 0; i < numVertice; i++)
        {
            for (size_t j = 0; j < numVertice; j++)
            {
                for (size_t k = 0; k < numVertice; k++)
                {
                    if(i != j)
                    {
                        matrixResult[i][j] += graph1[i][k] * graph2[k][j];
                    }
                }
            }
        }
        graphResult.loadGraph(matrixResult);
        return graphResult;
    }

} // ariel