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
    Graph::npds = Graph::structure->getNpds();
    Graph::tree = std::vector< std::tuple<int, int> >(Graph::structure->getN(), std::tuple<int, int>(-1, -1));
    Graph::ccMarked = std::vector<int>(Graph::n, 0);
    Graph::maxDist = 0;
    Graph::distSum = 0;
}

template <typename T>
Graph<T>::~Graph()
{
    delete Graph::structure, Graph::tree, Graph::ccMarked, Graph::ccs, Graph::ds, Graph::nds;
}

template <typename T>
T *Graph<T>::getStructure()
{
    return Graph::structure;
}

template <typename T>
std::vector< std::tuple<int,int> > Graph<T>::getTree()
{
    return Graph::tree;
}

template <typename T>
std::list< std::tuple< int, std::list<int> > > Graph<T>::getCcs()
{
    return Graph::ccs;
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
            writef << i << " " << (double) Graph::ds.at(i) / Graph::n << "\n";
        }
        writef << "\n";
        // writing spanning tree
        writef << "Spanning tree: \n";
        writef << "Node (Father, Level) \n";
        for (int i = 0; i < Graph::n; ++i)
        {
            writef << i + 1 << " (" << std::get<0>(Graph::tree.at(i)) + 1 << "," << std::get<1>(Graph::tree.at(i)) << ")\n";
        }
        writef << "\n";
        //writing connected components
        writef << "Connected components: " << Graph::ccs.size() << " components \n";
        Graph::ccs.sort(std::greater< std::tuple< int, std::list<int> > >());
        for (std::list< std::tuple< int, std::list<int> > >::iterator it = Graph::ccs.begin(); it != Graph::ccs.end(); ++it)
        {
            writef << std::get<0>(*it) << ": [";
            for (std::list<int>::iterator iti = std::get<1>(*it).begin(); iti != std::get<1>(*it).end(); ++iti)
            {
                writef << *iti + 1 << ", ";
            }
            writef << "] \n";
        }
    }
    writef.close();
}

template <typename T>
std::vector< std::tuple<int, float> > Graph<T>::getNeighbours(const int v)
{
    return Graph::structure->getNeighbours(v);
}

template <typename T>
std::list<int> Graph<T>::bfs(const int s)
{
    //int level = 0;
//    std::cout << "Started BFS ..." << std::endl;
//
//    clock_t startTime = clock();

    std::vector<int> marked(Graph::n, 0);
    std::queue<int> queue;
    std::list<int> covered;
    std::vector<int> coveredMarked(Graph::n, 0);


//    Graph::marked = std::vector<int>(Graph::n, 0);
//    Graph::queue = std::queue<int>();
//    Graph::covered = std::list<int>();
//    Graph::coveredMarked = std::vector<int>(Graph::n, 0);

    marked.at(s) = 1;
    queue.push(s);
    tree.at(s) = std::make_tuple(-1,0); //tree->at(s) = (-1,level);
    while (!queue.empty())
    {
        //++level;
        int vert = queue.front();
        queue.pop();


        if (coveredMarked.at(vert) == 0)
        {
            coveredMarked.at(vert) = 1;
            covered.push_back(vert);
        }

//        std::vector<int> neighbours = Graph::structure->getNeighbours(vert);
        Graph::neighbours = Graph::structure->getNeighbours(vert);
        for (std::vector< std::tuple<int, float> >::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            if (marked.at(std::get<0>(*it)) == 0)
            {
                marked.at(std::get<0>(*it)) = 1;
                Graph::ccMarked.at(std::get<0>(*it)) = 1;
                queue.push(std::get<0>(*it));
                tree.at(std::get<0>(*it)) = std::make_tuple (vert, std::get<1>(Graph::tree.at(vert)) + 1);
                //tree->at(*it) = std::make_tuple (vert,level); // stores 'vert' as the parent of the current node being marked, and 'level' as its level
                if (std::get<1>(Graph::tree.at(vert)) + 1 > Graph::maxDist)
                    Graph::maxDist = std::get<1>(Graph::tree.at(vert)) + 1;
            }
        }
//        delete neighbours;
    }
//    delete queue, marked;

//    clock_t endTime = clock();
//
//    std::cout << "Finished running BFS ..." << std::endl;
//    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;

    return covered;
}

template <typename T>
std::list<int> Graph<T>::dfs(const int s)
{
//    std::cout << "Started DFS ..." << std::endl;
//
//    clock_t startTime = clock();

    std::vector<int> marked(Graph::n, 0);
    std::stack<int> stack;
    std::list<int> covered;
    std::vector<int> coveredMarked(Graph::n, 0);

//    Graph::marked = std::vector<int>(Graph::n, 0);
//    Graph::stack = std::stack<int>();
//    Graph::covered = std::list<int>();
//    Graph::coveredMarked = std::vector<int>(Graph::n, 0);

    stack.push(s);
    tree.at(s) = std::make_tuple(-1,0);
    while (!stack.empty())
    {
        int vert = stack.top();
        stack.pop();

        if (coveredMarked.at(vert) == 0)
        {
            coveredMarked.at(vert) = 1;
            covered.push_back(vert);
        }

        if (marked.at(vert) == 0)
        {
            marked.at(vert) = 1;
            Graph::ccMarked.at(vert) = 1;
//            std::vector<int> neighbours = Graph::structure->getNeighbours(vert);
            Graph::neighbours = Graph::structure->getNeighbours(vert);
            for (std::vector< std::tuple<int, float> >::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
            {
                if (marked.at(std::get<0>(*it)) == 0)
                {
                    stack.push(std::get<0>(*it));
                    tree.at(std::get<0>(*it)) = std::make_tuple (vert, std::get<1>(Graph::tree.at(vert)) + 1);
                    if (std::get<1>(Graph::tree.at(vert)) + 1 > Graph::maxDist)
                        Graph::maxDist = std::get<1>(Graph::tree.at(vert)) + 1;
                }
            }
//            delete neighbours;
        }
    }
//    delete stack, marked;

//    clock_t endTime = clock();
//
//    std::cout << "Finished running DFS ..." << std::endl;
//    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;

    return covered;
}

template <typename T>
void Graph<T>::connectedComponents()
{
//    std::cout << "Started Connected Components ..." << std::endl;
//
//    clock_t startTime = clock();

    Graph::ccMarked = std::vector<int>(Graph::n, 0);
    Graph::ccs = std::list< std::tuple< int, std::list<int> > >();
    int ccCount = 0;
    for (int i = 0; i < Graph::n; ++i)
    {
        if (Graph::ccMarked.at(i) == 0)
        {
            ++ccCount;
            std::list<int> t = Graph::dfs(i);
            std::tuple<int, std::list<int> > cc = std::make_tuple(t.size(), t);
            ccs.push_back(cc);
//            delete t, cc;
        }
        std::cout << "CC NUMBER: " << ccCount << std::endl;
    }

//    clock_t endTime = clock();
//
//    std::cout << "Finished running Connected Components ..." << std::endl;
//    std::cout << "took " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;
}

template <typename T>
int Graph<T>::diameter()
{
    for (int i = 0; i < Graph::n; ++i)
    {
        Graph::bfs(i);
    }
    return Graph::maxDist;
}

// returns a list of tuples (node, dist) containing the distance from S to each node in the graph
template <typename T>
std::list< std::tuple<int, float> > Graph<T>::dijkstra(const int s)
{
    std::list< std::tuple <int, float> > list;
    if(Graph::getStructure()->hasNegativeEdges())
    {
        std::cout << "Can't run Dijkstra on a graph with negative weight edges." << std::endl;
        return list;
    }
    std::vector<float> dist(Graph::n, std::numeric_limits<float>::infinity());
    std::vector<bool> checked(Graph::n, false);
    std::priority_queue<Node, std::vector<Node>, std::greater<Node> > pQueue;

    dist.at(s) = 0;

    Node node(s, 0);
    pQueue.push(node);

    while (!pQueue.empty())
    {
        Node u = pQueue.top();
        checked.at(u.value) = true;
        pQueue.pop();
        Graph::neighbours = Graph::getNeighbours(u.value);
        for (int i = 0; i < Graph::neighbours.size(); ++i)
        {
            if (dist.at(std::get<0>(Graph::neighbours.at(i))) > dist.at(u.value) + std::get<1>(Graph::neighbours.at(i)))
            {
                if (!checked.at(std::get<0>(Graph::neighbours.at(i))))
                {
                    dist.at(std::get<0>(Graph::neighbours.at(i))) = dist.at(u.value) + std::get<1>(Graph::neighbours.at(i));
                    Node n(std::get<0>(Graph::neighbours.at(i)), dist.at(std::get<0>(Graph::neighbours.at(i))));
                    pQueue.push(n);
                }
            }
        }
    }
    for(int i = 0; i < Graph::n; ++i)
    {
        if(dist.at(i)!=std::numeric_limits<float>::infinity())
            Graph::distSum += dist.at(i);
    }
}

template <typename T>
std::list< std::tuple<int, float> > Graph<T>::prim(const int s)
{
    float totalCost = 0;
    std::vector<float> cost(Graph::n, std::numeric_limits<float>::infinity());
    std::vector<bool> checked(Graph::n, false);
    std::priority_queue<Node, std::vector<Node>, std::greater<Node> > pQueue;

    cost.at(s) = 0;
    Node node(s, 0);
    pQueue.push(node); // sets cost for MST containing only S to zero, and pushes S to pQueue

    while (!pQueue.empty())
    {
        Node u = pQueue.top();
        checked.at(u.value) = true;
        pQueue.pop();
        Graph::neighbours = Graph::getNeighbours(u.value);
        for (int i = 0; i < Graph::neighbours.size(); ++i)
        {
            if (cost.at(std::get<0>(Graph::neighbours.at(i))) > std::get<1>(Graph::neighbours.at(i)))
            {
                if (!checked.at(std::get<0>(Graph::neighbours.at(i))))
                {
                    cost.at(std::get<0>(Graph::neighbours.at(i))) = std::get<1>(Graph::neighbours.at(i));
                    Node n(std::get<0>(Graph::neighbours.at(i)), cost.at(std::get<0>(Graph::neighbours.at(i))));
                    pQueue.push(n);
                }
            }
        }
    }
    for(int i = 0; i < Graph::n; ++i)
    {
        totalCost += cost.at(i);
    }
    std::cout << "MST cost = " << totalCost << std::endl;
}

template <typename T>
float Graph<T>::getDistMedia()
{
    float media = 0;
    Graph::distSum = 0;
    for(int i = 0; i < Graph::n; ++i)
    {
        Graph::dijkstra(i);
    }

    if(Graph::n!=0)
        media = distSum / ((Graph::n * (Graph::n - 1)) / 2);

    return media;
}

template <typename T>
void Graph<T>::greedyColoring(std::list<int> order)
{
    // set all vertices with no color
    Graph::coloring = std::vector<int>(Graph::n, -1);
    // set the initial color
    int color = 0;
    bool prohibitColor = false;

    Graph::coloring[order.front()] = 0;
    order.pop_front();

    while (!order.empty())
    {
        for (std::list<int>::iterator it = order.begin(); it != order.end(); ++it)
        {
            Graph::neighbours = Graph::getNeighbours(*it);
            prohibitColor = false;
            for (int i = 0; i < Graph::neighbours.size(); ++i)
            {
                if (Graph::coloring[std::get<0>(Graph::neighbours[i])] == color) { prohibitColor = true; }
            }
            if (!prohibitColor)
            {
                Graph::coloring[*it] = color;
                order.erase(it);
            }
        }
        ++color;
    }

    std::cout << "Chromatic Number = " << color << std::endl;

    for (int i = 0; i < Graph::coloring.size(); ++i)
    {
        std::cout << i + 1 << ": " << Graph::coloring[i] << std::endl;
    }
}

template <typename T>
void Graph<T>::welshPowell()
{
    std::list<int> order;

    for (std::vector< std::list<int> >::reverse_iterator iti = Graph::npds.rbegin(); iti != Graph::npds.rend(); ++iti)
    {
        for (std::list<int>::iterator itj = iti->begin(); itj != iti->end(); ++itj)
        {
            order.push_back(*itj);
        }
    }

    Graph::greedyColoring(order);
}

template class Graph<AdjacencyMatrix>;
template class Graph<AdjacencyVector>;