#include <iostream>

#include "Graph.h"

//#define EXAMPLE_PATH "../git-repos/CGraph/graphs/example.txt"
//#define AS_GRAPH_PATH "../git-repos/CGraph/graphs/as_graph.txt"
//#define SUBDBLP_PATH "../git-repos/CGraph/graphs/subdblp.txt"
//#define DBLP_PATH "../git-repos/CGraph/graphs/dblp.txt"
//
//#define EXAMPLE_OUTPUT "../git-repos/CGraph/outputs/example_output.txt"
//#define AS_GRAPH_OUTPUT "../git-repos/CGraph/outputs/as_graph_output.txt"
//#define SUBDBLP_OUTPUT "../git-repos/CGraph/outputs/subdblp_output.txt"
//#define DBLP_OUTPUT "../git-repos/CGraph/outputs/dblp_output.txt"

#define EXAMPLE_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/example.txt"
#define AS_GRAPH_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/as_graph.txt"
#define SUBDBLP_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/subdblp.txt"
#define DBLP_PATH "/Users/ericreis/ClionProjects/CGraph/graphs/dblp.txt"

#define EXAMPLE_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/example_output.txt"
#define AS_GRAPH_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/as_graph_output.txt"
#define SUBDBLP_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/subdblp_output.txt"
#define DBLP_OUTPUT "/Users/ericreis/ClionProjects/CGraph/outputs/dblp_output.txt"

#define EXAMPLE_RESULT "/Users/ericreis/ClionProjects/CGraph/presentation_results/example_output.txt"
#define AS_GRAPH_RESULT "/Users/ericreis/ClionProjects/CGraph/presentation_results/as_graph_output.txt"
#define SUBDBLP_RESULT "/Users/ericreis/ClionProjects/CGraph/presentation_results/subdblp_output.txt"
#define DBLP_RESULT "/Users/ericreis/ClionProjects/CGraph/presentation_results/dblp_output.txt"

int main()
{
//    Graph<AdjacencyVector> g(AS_GRAPH_PATH);
//   	std::cout << *g.getStructure() << std::endl;
//
//    clock_t startTime = clock();
//
//    for (int i = 0; i < 10; ++i)
//    {
//        g.dfs(i * 10); // vertices: 0, 10, 20, ..., 100
//    }
//
//    clock_t endTime = clock();
//
//    std::cout << "T = " << (double(endTime - startTime) / (double)CLOCKS_PER_SEC) / 10 << std::endl;
//
//    g->bfs(0);
//    g->dfs(0);
//
//    g->connectedComponents();
//
//    g->generateOutput(DBLP_OUTPUT);


    std::ofstream writef(DBLP_RESULT);
    if (writef.is_open())
    {
        Graph<AdjacencyVector> g(DBLP_PATH);

        writef << "DBLP_GRAPH (130k vertices): \n";
        writef << "Tempo medio para executar 10 BFS: ";

        clock_t startTimeBfsAS = clock();

        for (int i = 0; i < 10; ++i)
        {
            g.bfs(i * 10); // vertices: 0, 10, 20, ..., 100
        }

        clock_t endTimeBfsAS = clock();

        std::cout << "AQUI: " << (double(endTimeBfsAS - startTimeBfsAS) / (double)CLOCKS_PER_SEC) / 10 << std::endl;
        writef << (double(endTimeBfsAS - startTimeBfsAS) / (double)CLOCKS_PER_SEC) / 10 << "\n";

        writef << "Tempo medio para executar 10 DFS: ";

        clock_t startTimeDfsAS = clock();

        for (int i = 0; i < 10; ++i)
        {
            g.dfs(i * 10); // vertices: 0, 10, 20, ..., 100
        }

        clock_t endTimeDfsAS = clock();

        writef << (double(endTimeDfsAS - startTimeDfsAS) / (double)CLOCKS_PER_SEC) / 10 << "\n";

        writef << "Pai dos vertices 10, 20, 30, 40, 50 comecando em 1, 2, 3, 4, 5: \n";
        writef << "BFS: \n";

        for (int i = 0; i < 5; ++i)
        {
            g.bfs(i);
            writef << i + 1 << ": ";
            for (int j = 1; j <= 5; ++j)
            {
                writef << std::get<0>(g.getTree().at(j * 10)) + 1 << ", ";
            }
            writef << "\n";
        }

        writef << "DFS: \n";

        for (int i = 0; i < 5; ++i)
        {
            g.dfs(i);
            writef << i + 1<< ": ";
            for (int j = 1; j <= 5; ++j)
            {
                writef << std::get<0>(g.getTree().at(j * 10)) + 1 << ", ";
            }
            writef << "\n";
        }

        writef << "Componentes conexas. Quantas tem, qual a maior e qual a maior? \n";
        writef << "Ver no final do output de cada grafo (ESTAO EM ORDEM DECRESCENTE, logo a primeira e a maior e a ultima a menor) \n";

//        g.connectedComponents();

        writef << "Distribuicao Empirica. Grafico \n";
        writef << "Ver no output de cada grafico tambem \n";

        writef << "Diametro. ??????\n\n";
    }
    writef.close();

    return 0;
}