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

#include "Constants.h"

class AdjacencyVector
{
private:
    int n, m, maxD;

    std::vector<int> *nds;      // Stores the degrees of each node
    std::vector<int> *ds;       // Stores the number of nodes of each degree
    std::vector< std::vector<int> > *vector;

    friend std::ostream &operator<< (std::ostream &out, const AdjacencyVector &v);

public:
    AdjacencyVector(const std::string file);
    ~AdjacencyVector();

    int getN() const;
    int getM() const;
    int getMaxD() const;
    std::vector<int> *getNds() const;
    std::vector<int> *getDs() const;
    std::vector< std::vector<int> > *getVector() const;
};


#endif //CGRAPH_ADJACENCYVECTOR_H
