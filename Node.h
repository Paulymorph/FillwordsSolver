//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_NODE_H
#define FILLWORDSSOLVER_NODE_H

#include "Edge.h"

#include <forward_list>

class Node
{
    std::forward_list<Edge> _edges;
public:
    Node() {}

    void add_edge(char value, Node* next);

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    Node* get_next(char c);

    bool is_leaf() const;
};


#endif //FILLWORDSSOLVER_NODE_H
