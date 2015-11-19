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
    int n, m;
    double mediumD;

    std::vector< std::vector<int> > *vector;

    friend std::ostream &operator<< (std::ostream &out, const AdjacencyVector &v);

public:
    AdjacencyVector(const std::string file);
    ~AdjacencyVector();

    int getN() const;
    int getM() const;
    double getMediumD() const;
    std::vector< std::vector<int> > *getVector() const;
};


#endif //CGRAPH_ADJACENCYVECTOR_H
