//
// Created by Paul Danilin on 05/04/2017.
//

#ifndef FILLWORDSSOLVER_VECTORNODE_H
#define FILLWORDSSOLVER_VECTORNODE_H

#include <array>
#include "../Edge.h"
#include "../Utilities.h"

class STL_ArrayNode : public AbstractNode
{
public:
    static const int ARRAY_SIZE = 34;

private:
    std::array<Edge, STL_ArrayNode::ARRAY_SIZE> _edges;

public:
    STL_ArrayNode(AbstractNode* prev);

    void add_edge(wchar_t value, AbstractNode* next);

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    AbstractNode* get_next(wchar_t c);

    ~STL_ArrayNode();
};


#endif //FILLWORDSSOLVER_VECTORNODE_H
