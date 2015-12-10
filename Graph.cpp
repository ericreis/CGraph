//
// Created by Eric Reis on 11/17/15.
//

#include "Graph.h"

template <typename T>
Graph<T>::Graph(const std::string file)
{
    Graph::structure = new T(file);
    Graph::n = Graph::structure->getN();
    Graph::m = Graph::structure->getM();
    Graph::maxD = Graph::structure->getMaxD();
    Graph::mediumD = 2.0 * Graph::m / Graph::n;
    Graph::nds = Graph::structure->getNds();
    Graph::ds = Graph::structure->getDs();
}

template <typename T>
Graph<T>::~Graph()
{
    delete Graph::structure;
}

template <typename T>
T *Graph<T>::getStructure()
{
    return Graph::structure;
}

template <typename T>
void Graph<T>::generateOutput(const std::string s)
{
    std::ofstream writef(s);
    if (writef.is_open())
    {
        writef << "# n = " << Graph::n << "\n";
        writef << "# m = " << Graph::m << "\n";
        writef << "# d_medio = " << Graph::mediumD << "\n";
        for (int i = 0; i <= Graph::maxD; ++i)
        {
            writef << i << " " << (double) Graph::ds->at(i) / Graph::n << "\n";
        }
    }
}

template <typename T>
std::vector<int> *Graph<T>::getNeighbours(const int v)
{
    return Graph::structure->getNeighbours(v);
}

template class Graph<AdjacencyMatrix>;
template class Graph<AdjacencyVector>;