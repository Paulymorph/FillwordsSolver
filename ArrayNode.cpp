//
// Created by Paul Danilin on 04/04/2017.
//
#include <stdexcept>
#include <iostream>

#include "ArrayNode.h"

int hash(wchar_t c)
{
    wchar_t result = (c - L'А') % ArrayNode::ARRAY_SIZE;
    if (result < 0)
    {
        std::wcout << c << std::endl;
        throw std::logic_error("Made the hash crazy!");
    }
    return result;
}

ArrayNode::ArrayNode(AbstractNode* prev)
{
    this->_prev = prev;
    _edges = new Edge[ARRAY_SIZE];
}

void ArrayNode::add_edge(wchar_t value, AbstractNode* next)
{
    if (_edges[hash(value)].get_next() != nullptr)
        throw std::logic_error("The edge was already initialized!");

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