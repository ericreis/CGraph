//
// Created by Eric Reis on 11/18/15.
//

#include "AdjacencyVector.h"

AdjacencyVector::AdjacencyVector(const std::string file)
{
    std::cout << "Reading graph file ..." << std::endl;

    clock_t startTime = clock();
    std::ifstream readf(file);
    std::string line;

    if (readf.is_open())
    {
        getline(readf, line);
        AdjacencyVector::n = Constants::string2int(line);

        std::cout << "Initializing empty Adjacency Matrix ..." << std::endl;
        AdjacencyVector::vector = new std::vector< std::vector<int> >(AdjacencyVector::n, std::vector<int>());
        std::cout << "Finished initialization" << std::endl;

        AdjacencyVector::m = 0;

        std::cout << "Filling Adjacency Vector ..." << std::endl;
        while (getline(readf, line))
        {
            ++AdjacencyVector::m;
            std::vector<std::string> v = Constants::split(line, ' ');
            int nodeA = Constants::string2int(v.at(0)) - 1;
            int nodeB = Constants::string2int(v.at(1)) - 1;
            AdjacencyVector::vector->at(nodeA).push_back(nodeB);
            AdjacencyVector::vector->at(nodeB).push_back(nodeA);
        }
        std::cout << "Finished filling the vector" << std::endl;
    }

    readf.close();
    clock_t endTime = clock();

    std::cout << "tooked " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

AdjacencyVector::~AdjacencyVector()
{
    delete AdjacencyVector::vector;
}

int AdjacencyVector::getN() const
{
    return AdjacencyVector::n;
}

int AdjacencyVector::getM() const
{
    return AdjacencyVector::m;
}

double AdjacencyVector::getMediumD() const
{
    return AdjacencyVector::mediumD;
}

std::vector< std::vector<int> > *AdjacencyVector::getVector() const
{
    return AdjacencyVector::vector;
}

std::ostream& operator<<(std::ostream &out, const AdjacencyVector &v)
{
    for (std::vector< std::vector<int> >::iterator iti = v.vector->begin(); iti != v.vector->end(); ++iti)
    {
        out << iti - v.vector->begin() + 1 << ": ";
        for (std::vector<int>::iterator itj = iti->begin(); itj != iti->end(); ++itj)
        {
            out << *itj + 1 << " ";
        }
        out << "\n";
    }
    return out;
}
