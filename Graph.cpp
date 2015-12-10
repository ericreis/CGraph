//
// Created by Eric Reis on 11/17/15.
//

#include "Graph.h"

template <typename T>
Graph<T>::Graph(const std::string file)
{
    Graph::structure = new T(file);
    Graph::n = Graph::structure->getN();
    Graph::m = Graph::structure->getM();
    Graph::maxD = Graph::structure->getMaxD();
    Graph::mediumD = 2.0 * Graph::m / Graph::n;
    Graph::nds = Graph::structure->getNds();
    Graph::ds = Graph::structure->getDs();
}

template <typename T>
Graph<T>::~Graph()
{
    delete Graph::structure;
}

template <typename T>
T *Graph<T>::getStructure()
{
    return Graph::structure;
}

template <typename T>
void Graph<T>::generateOutput(const std::string s)
{
    std::ofstream writef(s);
    if (writef.is_open())
    {
        writef << "# n = " << Graph::n << "\n";
        writef << "# m = " << Graph::m << "\n";
        writef << "# d_medio = " << Graph::mediumD << "\n";
        for (int i = 0; i <= Graph::maxD; ++i)
        {
            writef << i << " " << (double) Graph::ds->at(i) / Graph::n << "\n";
        }
    }
}

template <typename T>
std::vector<int> *Graph<T>::getNeighbours(const int v)
{
    return Graph::structure->getNeighbours(v);
}

template <typename T>
void Graph<T>::bfs(const int s)
{
    std::cout << "Started BFS ..." << std::endl;

    clock_t startTime = clock();

    std::vector<int> *marked = new std::vector<int>(Graph::n, 0);
    std::queue<int> *queue = new std::queue<int>();
    marked->at(s) = 1;
    queue->push(s);
    while (!queue->empty())
    {
        int vert = queue->front();
        queue->pop();
        std::vector<int> *neighbours = Graph::structure->getNeighbours(vert);
        for (std::vector<int>::iterator it = neighbours->begin(); it != neighbours->end(); ++it)
        {
            if (marked->at(*it) == 0)
            {
                marked->at(*it) = 1;
                queue->push(*it);
            }
        }
        delete neighbours;
    }
    delete queue, marked;

    clock_t endTime = clock();

    std::cout << "Finished running BFS ..." << std::endl;
    std::cout << "tooked " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

template <typename T>
void Graph<T>::dfs(const int s)
{
    std::cout << "Started DFS ..." << std::endl;

    clock_t startTime = clock();

    std::vector<int> *marked = new std::vector<int>(Graph::n, 0);
    std::stack<int> *stack = new std::stack<int>();
//    marked->at(s) = 1;
    stack->push(s);
    while (!stack->empty())
    {
        int vert = stack->top();
        stack->pop();

        if (marked->at(vert) == 0)
        {
            marked->at(vert) = 1;
            std::vector<int> *neighbours = Graph::structure->getNeighbours(vert);
            for (std::vector<int>::iterator it = neighbours->begin(); it != neighbours->end(); ++it)
            {
                stack->push(*it);
            }
            delete neighbours;
        }

//        std::vector<int> *neighbours = Graph::structure->getNeighbours(vert);
//        for (std::vector<int>::iterator it = neighbours->begin(); it != neighbours->end(); ++it)
//        {
//            if (marked->at(*it) == 0)
//            {
//                marked->at(*it) = 1;
//                stack->push(*it);
//            }
//        }
//        delete neighbours;
    }
    delete stack, marked;

    clock_t endTime = clock();

    std::cout << "Finished running DFS ..." << std::endl;
    std::cout << "tooked " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

template class Graph<AdjacencyMatrix>;
template class Graph<AdjacencyVector>;