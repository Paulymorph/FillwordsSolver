//
// Created by Paul Danilin on 05/04/2017.
//

#include "STL_ArrayNode.h"

#include <iostream>

STL_ArrayNode::STL_ArrayNode(AbstractNode* prev)
{
    this->_prev = prev;
}

void STL_ArrayNode::add_edge(wchar_t value, AbstractNode* next)
{
    if (_edges[hash(value, STL_ArrayNode::ARRAY_SIZE)].get_next() != nullptr)
        throw std::logic_error("The edge was already initialized!");

    _edges[hash(value, STL_ArrayNode::ARRAY_SIZE)] = Edge(value, next);
}

AbstractNode* STL_ArrayNode::get_next(wchar_t c)
{
    return _edges[hash(c, STL_ArrayNode::ARRAY_SIZE)].get_next();
}

STL_ArrayNode::~STL_ArrayNode()
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        delete _edges[i].get_next();
    }
}