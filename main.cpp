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

#define EXAMPLE_PATH "../CGraph/graphs/example.txt"
#define AS_GRAPH_PATH "../CGraph/graphs/as_graph.txt"
#define SUBDBLP_PATH "../CGraph/graphs/subdblp.txt"
#define DBLP_PATH "../CGraph/graphs/dblp.txt"

#define EXAMPLE_OUTPUT "../CGraph/outputs/example_output.txt"
#define AS_GRAPH_OUTPUT "../CGraph/outputs/as_graph_output.txt"
#define SUBDBLP_OUTPUT "../CGraph/outputs/subdblp_output.txt"
#define DBLP_OUTPUT "../CGraph/outputs/dblp_output.txt"

#define EXAMPLE_RESULT "../CGraph/presentation_results/example_output.txt"
#define AS_GRAPH_RESULT "../CGraph/presentation_results/as_graph_output.txt"
#define SUBDBLP_RESULT "../CGraph/presentation_results/subdblp_output.txt"
#define DBLP_RESULT "../CGraph/presentation_results/dblp_output.txt"

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <stdio.h>

#endif

#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif

size_t getPeakRSS( );
size_t getCurrentRSS( );

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
    size_t startMem, endMem;

    std::ofstream writef(DBLP_RESULT);
    if (writef.is_open())
    {
        startMem = getCurrentRSS();
        Graph<AdjacencyVector> g(DBLP_PATH);
        endMem = getCurrentRSS();
        std::cout << "Memory usage: " << endMem - startMem << " bytes.";

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

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 */
size_t getPeakRSS( )
{
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (size_t)info.PeakWorkingSetSize;

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
    /* AIX and Solaris ------------------------------------------ */
    struct psinfo psinfo;
    int fd = -1;
    if ( (fd = open( "/proc/self/psinfo", O_RDONLY )) == -1 )
        return (size_t)0L;      /* Can't open? */
    if ( read( fd, &psinfo, sizeof(psinfo) ) != sizeof(psinfo) )
    {
        close( fd );
        return (size_t)0L;      /* Can't read? */
    }
    close( fd );
    return (size_t)(psinfo.pr_rssize * 1024L);

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    /* BSD, Linux, and OSX -------------------------------------- */
    struct rusage rusage;
    getrusage( RUSAGE_SELF, &rusage );
#if defined(__APPLE__) && defined(__MACH__)
    return (size_t)rusage.ru_maxrss;
#else
    return (size_t)(rusage.ru_maxrss * 1024L);
#endif

#else
    /* Unknown OS ----------------------------------------------- */
    return (size_t)0L;          /* Unsupported. */
#endif
}

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentRSS( )
{
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (size_t)info.WorkingSetSize;

#elif defined(__APPLE__) && defined(__MACH__)
    /* OSX ------------------------------------------------------ */
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if ( task_info( mach_task_self( ), MACH_TASK_BASIC_INFO,
        (task_info_t)&info, &infoCount ) != KERN_SUCCESS )
        return (size_t)0L;      /* Can't access? */
    return (size_t)info.resident_size;

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    /* Linux ---------------------------------------------------- */
    long rss = 0L;
    FILE* fp = NULL;
    if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
        return (size_t)0L;      /* Can't open? */
    if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
    {
        fclose( fp );
        return (size_t)0L;      /* Can't read? */
    }
    fclose( fp );
    return (size_t)rss * (size_t)sysconf( _SC_PAGESIZE);

#else
    /* AIX, BSD, Solaris, and Unknown OS ------------------------ */
    return (size_t)0L;          /* Unsupported. */
#endif
}