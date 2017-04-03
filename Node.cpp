//
// Created by Paul Danilin on 04/04/2017.
//

#include "Node.h"

void Node::add_edge(char value, Node* next)
{
    _edges.push_front(Edge(value, next));
}

Node* Node::get_next(char c)
{
    for (Edge e: _edges)
    {
        if (e.get_value() == c)
            return e.get_next();
    }

    return nullptr;
}

bool Node::is_leaf() const
{ return _edges.empty(); }