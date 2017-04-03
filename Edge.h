//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_EDGE_H
#define FILLWORDSSOLVER_EDGE_H

class Node;

/**
 * Edge is an object pointering from one node to another.
 */
class Edge
{
    /// The char of the transfer.
    char _value;
    /// The next node of the edge.
    Node* _next;

public:
    Edge(char value, Node* next) : _value(value), _next(next)
    {}

    char get_value() const
    {
        return _value;
    }

    Node* get_next() const
    {
        return _next;
    }
};


#endif //FILLWORDSSOLVER_EDGE_H
