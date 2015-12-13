#include <iostream>

#include "Graph.h"

#define EXAMPLE_PATH "../git-repos/CGraph/graphs/example.txt"
#define AS_GRAPH_PATH "../git-repos/CGraph/graphs/as_graph.txt"
#define SUBDBLP_PATH "../git-repos/CGraph/graphs/subdblp.txt"
#define DBLP_PATH "../git-repos/CGraph/graphs/dblp.txt"

#define EXAMPLE_OUTPUT "../git-repos/CGraph/outputs/example_output.txt"
#define AS_GRAPH_OUTPUT "../git-repos/CGraph/outputs/as_graph_output.txt"
#define SUBDBLP_OUTPUT "../git-repos/CGraph/outputs/subdblp_output.txt"
#define DBLP_OUTPUT "../git-repos/CGraph/outputs/dblp_output.txt"

int main()
{
    Graph<AdjacencyVector> *g = new Graph<AdjacencyVector>(EXAMPLE_PATH);
//   	std::cout << *g->getStructure() << std::endl;
    //g->generateOutput(EXAMPLE_OUTPUT);

    g->bfs(0);
    //g->dfs(0);

    g->generateOutput(EXAMPLE_OUTPUT);

    return 0;
}