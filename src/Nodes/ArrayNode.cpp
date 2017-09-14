//
// Created by Paul Danilin on 04/04/2017.
//
#include <stdexcept>

#include "ArrayNode.h"
#include "../Utilities.h"

ArrayNode::ArrayNode(AbstractNode* prev)
{
    this->_prev = prev;
    _edges = new Edge[ARRAY_SIZE];
}

void ArrayNode::add_edge(wchar_t value, AbstractNode* next)
{
    int hash_val = hash(value, ArrayNode::ARRAY_SIZE);
    if (_edges[hash_val].get_next() != nullptr)
        throw std::logic_error("The edge was already initialized!");

    _edges[hash_val] = Edge(value, next);
}

AbstractNode* ArrayNode::get_next(wchar_t c)
{
    return _edges[hash(c, ArrayNode::ARRAY_SIZE)].get_next();
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