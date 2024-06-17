//ID : 207723198
//Mail : yair852258@gmail.com

#ifndef GRAPHOPERATORS_H
#define GRAPHOPERATORS_H
#include "Graph.hpp"
#include <vector>

namespace ariel {

    // + operator
    Graph operator+(const Graph &graph1, const Graph &graph2);

    // + operator
    Graph operator-(const Graph &graph1, const Graph &graph2);

    // > operator
    bool operator>(const Graph& g1, const Graph& g2);

    // == operator
    bool operator==(const Graph& g1, const Graph& g2);

    // >= operator
    bool operator>=(const Graph& g1, const Graph& g2);

    // < operator
    bool operator<(const Graph& g1, const Graph& g2);

    // <= operator
    bool operator<=(const Graph& g1, const Graph& g2);

    // != operator
    bool operator!=(const Graph& g1, const Graph& g2);

} // ariel

#endif //GRAPHOPERATORS_H
