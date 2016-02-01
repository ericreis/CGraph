//
// Created by Eric Reis on 11/18/15.
//

#ifndef CGRAPH_ADJACENCYVECTOR_H
#define CGRAPH_ADJACENCYVECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

#include "Constants.h"

class AdjacencyVector
{
private:
    int n, m, maxD;
    bool hasNegative; // true if the graph contains at least one negative weight edge

    std::vector<int> nds;      // Stores the degrees of each node
    std::vector<int> ds;       // Stores the number of nodes of each degree
    std::vector< std::vector< std::tuple<int, float> > > vector;

    friend std::ostream &operator<< (std::ostream &out, const AdjacencyVector &v);

public:
    AdjacencyVector(const std::string file);
    ~AdjacencyVector();

    int getN() const;
    int getM() const;
    int getMaxD() const;
    bool getDijkstraCompatibility() const;
    std::vector<int> getNds() const;
    std::vector<int> getDs() const;
    std::vector< std::vector< std::tuple<int, float> > > getVector() const;

    std::vector< std::tuple<int, float> > &getNeighbours(int v);
};


#endif //CGRAPH_ADJACENCYVECTOR_H
