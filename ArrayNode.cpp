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

void ArrayNode::add_edge(char value, AbstractNode* next)
{
    _edges[hash(value)] = Edge(value, next);
}

AbstractNode* ArrayNode::get_next(char c)
{
    return (ArrayNode*) _edges[hash(c)].get_next();
}