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
        AdjacencyMatrix::matrix = new std::vector< std::vector<int> >(AdjacencyMatrix::n, std::vector<int>(AdjacencyMatrix::n));
        std::cout << "Finished initialization" << std::endl;

        AdjacencyMatrix::m = 0;

        std::cout << "Filling Adjacency Matrix ..." << std::endl;
        while (getline(readf, line))
        {
            ++AdjacencyMatrix::m;
            std::vector<std::string> v = Constants::split(line, ' ');
            int nodeA = Constants::string2int(v.at(0)) - 1;
            int nodeB = Constants::string2int(v.at(1)) - 1;
            AdjacencyMatrix::matrix->at(nodeA).at(nodeB) = 1;
            AdjacencyMatrix::matrix->at(nodeB).at(nodeA) = 1;
        }
        std::cout << "Finished filling the matrix" << std::endl;
    }

    readf.close();
    clock_t endTime = clock();

    std::cout << "tooked " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    delete AdjacencyMatrix::matrix;
}

int AdjacencyMatrix::getN() const
{
    return AdjacencyMatrix::n;
}

int AdjacencyMatrix::getM() const
{
    return AdjacencyMatrix::m;
}

double AdjacencyMatrix::getMediumD() const
{
    return AdjacencyMatrix::mediumD;
}

std::vector< std::vector<int> >* AdjacencyMatrix::getMatrix() const
{
    return AdjacencyMatrix::matrix;
}

std::ostream& operator<<(std::ostream &out, const AdjacencyMatrix &m)
{
    for (std::vector< std::vector<int> >::iterator iti = m.matrix->begin(); iti != m.matrix->end(); ++iti)
    {
        for (std::vector<int>::iterator itj = iti->begin(); itj != iti->end(); ++itj)
        {
            out << *itj << " ";
        }
        out << "\n";
    }
    return out;
}


