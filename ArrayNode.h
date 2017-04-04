//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_ARRAYNODE_H
#define FILLWORDSSOLVER_ARRAYNODE_H

#include "Edge.h"

class ArrayNode : public AbstractNode
{
    const int ARRAY_SIZE = 34;
    Edge* _edges;
public:
    ArrayNode();

    void add_edge(char value, AbstractNode* next);

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    AbstractNode* get_next(char c);

    ~ArrayNode()
    {
        delete[] _edges;
    }
};


#endif //FILLWORDSSOLVER_ARRAYNODE_H
