//
// Created by Eric Reis on 1/30/16.
//

#ifndef CGRAPH_NODE_H
#define CGRAPH_NODE_H

#include <iostream>

class Node
{
public:
    int value;
    float weight;

    Node(int value, float weight);
    ~Node();

    friend bool operator< (const Node &node1, const Node &node2);
    friend bool operator> (const Node &node1, const Node &node2);
    friend std::ostream &operator<< (std::ostream &out, const Node &node);
};


#endif //CGRAPH_NODE_H
