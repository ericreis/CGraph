//
// Created by Eric Reis on 1/30/16.
//

#include "Node.h"

Node::Node(int value, float weight)
{
    Node::value = value;
    Node::weight = weight;
}

Node::~Node()
{

}

bool operator<(const Node &node1, const Node &node2)
{
    return node1.weight < node2.weight;
}

bool operator>(const Node &node1, const Node &node2)
{
    return node1.weight > node2.weight;
}

std::ostream &operator<< (std::ostream &out, const Node &node)
{
    out << node.value + 1 << " - " << node.weight;
}