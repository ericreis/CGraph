//
// Created by Eric Reis on 11/18/15.
//

#include <list>
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
        AdjacencyVector::vector = std::vector< std::vector< std::tuple<int, float> > >(AdjacencyVector::n, std::vector< std::tuple<int, float> >());
        std::cout << "Finished initialization" << std::endl;

        AdjacencyVector::m = 0;
        AdjacencyVector::maxD = 0;
        AdjacencyVector::nds = std::vector<int>(AdjacencyVector::n, 0);

        std::cout << "Filling Adjacency Vector ..." << std::endl;
        while (getline(readf, line))
        {
            ++AdjacencyVector::m;
            std::vector<std::string> v = Constants::split(line, ' ');
            int nodeA = Constants::string2int(v.at(0)) - 1;
            int nodeB = Constants::string2int(v.at(1)) - 1;

            float weight;
            try
            {
                weight = Constants::string2float(v.at(2));
            }
            catch (std::exception& e)
            {
                weight = 1.0f;
            }

            AdjacencyVector::vector.at(nodeA).push_back(std::make_tuple(nodeB, weight));
            AdjacencyVector::vector.at(nodeB).push_back(std::make_tuple(nodeA, weight));

            ++AdjacencyVector::nds.at(nodeA);
            ++AdjacencyVector::nds.at(nodeB);

            // Updates the maximum degree value for the graph
            if (AdjacencyVector::nds.at(nodeA) > AdjacencyVector::maxD)
            {
                AdjacencyVector::maxD = AdjacencyVector::nds.at(nodeA);
            }
            else if (AdjacencyVector::nds.at(nodeB) > AdjacencyVector::maxD)
            {
                AdjacencyVector::maxD = AdjacencyVector::nds.at(nodeB);
            }
        }
        std::cout << "Finished filling the vector" << std::endl;
    }
    readf.close();

    std::cout << "Storing relative frequencies ..." << std::endl;
    // As an node can have degree 0, we need to create a vector of size maxD + 1
    AdjacencyVector::ds = std::vector<int>(AdjacencyVector::maxD + 1, 0);
    for (std::vector<int>::iterator it = AdjacencyVector::nds.begin(); it != AdjacencyVector::nds.end(); ++it)
    {
        ++AdjacencyVector::ds.at(*it);
    }
    std::cout << "Finished storing frequencies" << std::endl;

    clock_t endTime = clock();

    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

AdjacencyVector::~AdjacencyVector()
{
//    delete AdjacencyVector::vector, AdjacencyVector::ds, AdjacencyVector::nds;
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

std::vector<int> AdjacencyVector::getDs() const
{
    return AdjacencyVector::ds;
}

std::vector<int> AdjacencyVector::getNds() const
{
    return AdjacencyVector::nds;
}

std::vector< std::vector< std::tuple<int, float> > > AdjacencyVector::getVector() const
{
    return AdjacencyVector::vector;
}

std::ostream& operator<<(std::ostream &out, const AdjacencyVector &v)
{
//    for (std::vector< std::vector< std::tuple<int, float> > >::iterator iti = v.getVector().begin(); iti != v.getVector().end(); ++iti)
//    {
//        out << iti - v.getVector().begin() + 1 << ": ";
//        std::cout << iti->size() << std::endl;
//        for (std::vector< std::tuple<int, float> >::iterator itj = iti->begin(); itj != iti->end(); ++itj)
//        {
//            std::cout << std::get<0>(*itj) << std::endl;
//            out << std::get<0>(*itj) << " " << std::get<1>(*itj) << " ";
//        }
//        out << "\n";
//    }

    for (int i = 0; i < v.getVector().size(); ++i)
    {
        out << i + 1 << ": ";
        for (int j = 0; j < v.getVector().at(i).size(); ++j)
        {
            out << std::get<0>(v.getVector().at(i).at(j)) + 1 << " - " << std::get<1>(v.getVector().at(i).at(j)) << " ";
        }
        out << "\n";
    }

    return out;
}

std::vector< std::tuple<int, float> > &AdjacencyVector::getNeighbours(int v)
{
    if (v < AdjacencyVector::n)
    {
        return AdjacencyVector::vector.at(v);
    }
    else
    {
        throw std::invalid_argument("AdjacencyVector: node not in graph");
    }
}
