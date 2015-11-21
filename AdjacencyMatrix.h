//
// Created by Eric Reis on 11/17/15.
//

#ifndef CGRAPH_ADJACENCYMATRIX_H
#define CGRAPH_ADJACENCYMATRIX_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Constants.h"

class AdjacencyMatrix
{
private:
    int n, m, maxD;

    std::vector<int> *nds;      // Stores the degrees of each node
    std::vector<int> *ds;       // Stores the number of nodes of each degree
    std::vector< std::vector<int> > *matrix;

    friend std::ostream &operator<< (std::ostream &out, const AdjacencyMatrix &m);

public:
    AdjacencyMatrix(const std::string file);
    ~AdjacencyMatrix();

    int getN() const;
    int getM() const;
    int getMaxD() const;
    std::vector<int> *getNds() const;
    std::vector<int> *getDs() const;
    std::vector< std::vector<int> > *getMatrix() const;
};


#endif //CGRAPH_ADJACENCYMATRIX_H
