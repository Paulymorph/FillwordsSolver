//
// Created by Paul Danilin on 04/04/2017.
//

#include "ArrayNode.h"

int hash(wchar_t c)
{
    return c - L'А';
}

ArrayNode::ArrayNode()
{
    _edges = new Edge[ARRAY_SIZE];
}

void ArrayNode::add_edge(wchar_t value, AbstractNode* next)
{
    _edges[hash(value)] = Edge(value, next);
}

AbstractNode* ArrayNode::get_next(wchar_t c)
{
    return _edges[hash(c)].get_next();
}

ArrayNode::~ArrayNode()
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        delete _edges[i].get_next();
    }

    delete[] _edges;
    _edges = nullptr;
}