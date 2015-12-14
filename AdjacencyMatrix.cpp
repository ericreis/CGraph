//
// Created by Eric Reis on 11/17/15.
//

#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const std::string file)
{
    std::cout << "Reading graph file ..." << std::endl;

    clock_t startTime = clock();
    std::ifstream readf(file);
    std::string line;

    if (readf.is_open())
    {
        getline(readf, line);
        AdjacencyMatrix::n = Constants::string2int(line);

        std::cout << "Initializing empty Adjacency Matrix ..." << std::endl;
        AdjacencyMatrix::matrix = std::vector< std::vector<int> >(AdjacencyMatrix::n, std::vector<int>(AdjacencyMatrix::n));
        std::cout << "Finished initialization" << std::endl;

        AdjacencyMatrix::m = 0;
        AdjacencyMatrix::maxD = 0;
        AdjacencyMatrix::nds = std::vector<int>(AdjacencyMatrix::n, 0);

        std::cout << "Filling Adjacency Matrix ..." << std::endl;
        while (getline(readf, line))
        {
            ++AdjacencyMatrix::m;
            std::vector<std::string> v = Constants::split(line, ' ');
            int nodeA = Constants::string2int(v.at(0)) - 1;
            int nodeB = Constants::string2int(v.at(1)) - 1;

            AdjacencyMatrix::matrix.at(nodeA).at(nodeB) = 1;
            AdjacencyMatrix::matrix.at(nodeB).at(nodeA) = 1;

            ++AdjacencyMatrix::nds.at(nodeA);
            ++AdjacencyMatrix::nds.at(nodeB);

            // Updates the maximum degree value for the graph
            if (AdjacencyMatrix::nds.at(nodeA) > AdjacencyMatrix::maxD)
            {
                AdjacencyMatrix::maxD = AdjacencyMatrix::nds.at(nodeA);
            }
            else if (AdjacencyMatrix::nds.at(nodeB) > AdjacencyMatrix::maxD)
            {
                AdjacencyMatrix::maxD = AdjacencyMatrix::nds.at(nodeB);
            }
        }
        std::cout << "Finished filling the matrix" << std::endl;
    }
    readf.close();

//    std::cout << "Storing relative frequencies ..." << std::endl;
//    // As an node can have degree 0, we need to create a vector of size maxD + 1
//    AdjacencyMatrix::ds = std::vector<int>(AdjacencyMatrix::maxD + 1, 0);
//    for (std::vector<int>::iterator it = AdjacencyMatrix::nds.begin(); it != AdjacencyMatrix::nds.end(); ++it)
//    {
//        std::cout << it - AdjacencyMatrix::nds.begin() << std::endl;
//        ++AdjacencyMatrix::ds.at(it - AdjacencyMatrix::nds.begin());
//    }
//    std::cout << "Finished storing frequencies" << std::endl;

    clock_t endTime = clock();

    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

AdjacencyMatrix::~AdjacencyMatrix()
{
//    delete AdjacencyMatrix::matrix, AdjacencyMatrix::ds, AdjacencyMatrix::nds;
}

int AdjacencyMatrix::getN() const
{
    return AdjacencyMatrix::n;
}

int AdjacencyMatrix::getM() const
{
    return AdjacencyMatrix::m;
}

int AdjacencyMatrix::getMaxD() const
{
    return AdjacencyMatrix::maxD;
}

std::vector<int> AdjacencyMatrix::getNds() const
{
    return AdjacencyMatrix::nds;
}

std::vector<int> AdjacencyMatrix::getDs() const
{
    return AdjacencyMatrix::ds;
}

std::vector< std::vector<int> > AdjacencyMatrix::getMatrix() const
{
    return AdjacencyMatrix::matrix;
}

std::ostream& operator<<(std::ostream &out, const AdjacencyMatrix &m)
{
    for (std::vector< std::vector<int> >::iterator iti = m.getMatrix().begin(); iti != m.getMatrix().end(); ++iti)
    {
        for (std::vector<int>::iterator itj = iti->begin(); itj != iti->end(); ++itj)
        {
            out << *itj << " ";
        }
        out << "\n";
    }
    return out;
}

std::vector<int> &AdjacencyMatrix::getNeighbours(int v)
{
    if (v < AdjacencyMatrix::n)
    {
        AdjacencyMatrix::neighbours = std::vector<int>(AdjacencyMatrix::nds.at(v), 0);
        int neighbourIndex = 0;
        for (std::vector<int>::iterator it = AdjacencyMatrix::matrix.at(v).begin(); it != AdjacencyMatrix::matrix.at(v).end(); ++it)
        {
            if (*it == 1)
            {
                AdjacencyMatrix::neighbours.at(neighbourIndex) = it - AdjacencyMatrix::matrix.at(v).begin();
                ++neighbourIndex;
            }
        }
        return AdjacencyMatrix::neighbours;
    }
    else
    {
        throw std::invalid_argument("AdjacencyMatrix: node not in graph");
    }
}


