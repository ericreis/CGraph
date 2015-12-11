//
// Created by Eric Reis on 11/17/15.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

#include "AdjacencyMatrix.h"
#include "AdjacencyVector.h"

#include <queue>
#include <stack>


template <typename T>
class Graph
{
private:
    int n, m, maxD;
    double mediumD;

    std::vector<int> *nds;      // Stores the degree of each node
    std::vector<int> *ds;       // Stores the nodes of each degree
    T *structure;

    std::vector< std::tuple<int,int> > *tree; // Stores the parent and level of each node in the spanning tree, in the format: (parent,level)

public:
    Graph(const std::string file);
    ~Graph();

    T *getStructure();

    void generateOutput(const std::string s);
    std::vector<int> *getNeighbours(const int v);

    void bfs(const int s);
    void dfs(const int s);
};


#endif //CGRAPH_GRAPH_H
