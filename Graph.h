//
// Created by Eric Reis on 11/17/15.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

#include "AdjacencyMatrix.h"
#include "AdjacencyVector.h"

#include <queue>
#include <stack>
#include <tuple>
#include <list>
#include <limits>

#include "Node.h"

template <typename T>
class Graph
{
private:
    int n, m, maxD;
    double mediumD;
    bool hasNegative;

    int maxDist;

    std::vector<int> nds;      // Stores the degree of each node
    std::vector<int> ds;       // Stores the nodes of each degree
    T *structure;
//
    std::vector<int> marked;
    std::queue<int> queue;
    std::stack<int> stack;
    std::list<int> covered;
    std::vector<int> coveredMarked;
    std::vector< std::tuple<int, float> > neighbours;

    std::vector< std::tuple<int,int> > tree; // Stores the parent and level of each node in the spanning tree, in the format: (parent,level)

    std::vector<int> ccMarked; // Mark vector used in connectedComponents method
    std::list< std::tuple< int, std::list<int> > > ccs;   // Stores the connected components (size of cc, vector of cc's elements)

public:
    Graph(const std::string file);
    ~Graph();

    T *getStructure();
    std::vector< std::tuple<int,int> > getTree();
    std::list< std::tuple< int, std::list<int> > > getCcs();

    void generateOutput(const std::string s);
    std::vector< std::tuple<int, float> > getNeighbours(const int v);

    // first delivery
    std::list<int> bfs(const int s);
    std::list<int> dfs(const int s);
    void connectedComponents();
    int diameter();

    // second delivery
    bool hasNegativeEdges();
    std::list< std::tuple<int, float> > dijkstra(const int s);
};


#endif //CGRAPH_GRAPH_H
