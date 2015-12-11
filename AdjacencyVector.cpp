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

        std::cout << "Initializing empty Adjacency Vector ..." << std::endl;
        AdjacencyVector::vector = new std::vector< std::vector<int> >(AdjacencyVector::n, std::vector<int>());
        std::cout << "Finished initialization" << std::endl;

        AdjacencyVector::m = 0;
        AdjacencyVector::maxD = 0;
        AdjacencyVector::nds = new std::vector<int>(AdjacencyVector::n, 0);

        std::cout << "Filling Adjacency Vector ..." << std::endl;
        while (getline(readf, line))
        {
            ++AdjacencyVector::m;
            std::vector<std::string> v = Constants::split(line, ' ');
            int nodeA = Constants::string2int(v.at(0)) - 1;
            int nodeB = Constants::string2int(v.at(1)) - 1;
            AdjacencyVector::vector->at(nodeA).push_back(nodeB);
            AdjacencyVector::vector->at(nodeB).push_back(nodeA);

            ++AdjacencyVector::nds->at(nodeA);
            ++AdjacencyVector::nds->at(nodeB);

            // Updates the maximum degree value for the graph
            if (AdjacencyVector::nds->at(nodeA) > AdjacencyVector::maxD)
            {
                AdjacencyVector::maxD = AdjacencyVector::nds->at(nodeA);
            }
            else if (AdjacencyVector::nds->at(nodeB) > AdjacencyVector::maxD)
            {
                AdjacencyVector::maxD = AdjacencyVector::nds->at(nodeB);
            }
        }
        std::cout << "Finished filling the vector" << std::endl;
    }
    readf.close();

    std::cout << "Storing relative frequencies ..." << std::endl;
    // As an node can have degree 0, we need to create a vector of size maxD + 1
    AdjacencyVector::ds = new std::vector<int>(AdjacencyVector::maxD + 1, 0);
    for (std::vector<int>::iterator it = AdjacencyVector::nds->begin(); it != AdjacencyVector::nds->end(); ++it)
    {
        ++AdjacencyVector::ds->at(*it);
    }
    std::cout << "Finished storing frequencies" << std::endl;

    clock_t endTime = clock();

    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
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

int AdjacencyVector::getMaxD() const
{
    return AdjacencyVector::maxD;
}

std::vector<int>* AdjacencyVector::getDs() const
{
    return AdjacencyVector::ds;
}

std::vector<int> *AdjacencyVector::getNds() const
{
    return AdjacencyVector::nds;
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

std::vector<int> *AdjacencyVector::getNeighbours(int v)
{
    if (v < AdjacencyVector::n)
    {
        std::vector<int> *neighbours = new std::vector<int>(AdjacencyVector::vector->at(v));
        return neighbours;
    }
    else
    {
        throw std::invalid_argument("AdjacencyVector: node not in graph");
    }
}
