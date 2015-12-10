#include <iostream>

#include "Graph.h"

#define EXAMPLE_PATH "/home/fabricio/Desktop/CGraph/graphs/example.txt"
#define AS_GRAPH_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/as_graph.txt"
#define SUBDBLP_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/subdblp.txt"
#define DBLP_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/dblp.txt"

#define EXAMPLE_OUTPUT "/home/fabricio/Desktop/CGraph/outputs/example_output.txt"
#define AS_GRAPH_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/as_graph_output.txt"
#define SUBDBLP_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/subdblp_output.txt"
#define DBLP_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/dblp_output.txt"

int main()
{
    Graph<AdjacencyMatrix> *g = new Graph<AdjacencyMatrix>(EXAMPLE_PATH);
   	std::cout << *g->getStructure() << std::endl;
    g->generateOutput(EXAMPLE_OUTPUT);

    std::vector<int> *v = g->getNeighbours(0);
    for (std::vector<int>::iterator i = v->begin(); i != v->end(); ++i)
    {
    	std::cout << *i << std::endl;
    }

    return 0;
}