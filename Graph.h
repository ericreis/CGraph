//
// Created by Eric Reis on 11/17/15.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H

#include "AdjacencyMatrix.h"
#include "AdjacencyVector.h"


template <typename T>
class Graph
{
private:
    int n, m;
    double mediumD;

    T *structure;

public:
    Graph(const std::string file);
    ~Graph();

    T *getStructure();

    void generateOutput(const std::string s);

};


#endif //CGRAPH_GRAPH_H
