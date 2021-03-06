//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_EDGE_H
#define FILLWORDSSOLVER_EDGE_H

#include "Nodes/AbstractNode.h"

/**
 * Edge is an object pointering from one node to another.
 */
class Edge
{
    /// The char of the transfer.
    wchar_t _value;
    /// The next node of the edge.
    AbstractNode* _next;

public:
    Edge() : _value(' '), _next(nullptr)
    {}

    Edge(wchar_t value, AbstractNode* next) : _value(value), _next(next)
    {}

    wchar_t get_value() const
    {
        return _value;
    }

    AbstractNode* get_next() const
    {
        return _next;
    }
};


#endif //FILLWORDSSOLVER_EDGE_H
