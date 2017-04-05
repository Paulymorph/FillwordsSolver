//
// Created by Air_R on 05.04.17.
//

#ifndef FILLWORDSSOLVER_HASHNODE_H
#define FILLWORDSSOLVER_HASHNODE_H


#include <unordered_map>
#include "AbstractNode.h"
#include "Edge.h"

class HashNode : public AbstractNode
{
    std::unordered_map <wchar_t, Edge> _edges;
public:
    HashNode(AbstractNode* prev)
    {
        this->
                _prev = prev;
    }

    void add_edge(wchar_t value, AbstractNode* next);

/**
 * Finds the next node with the edge with the char.
 * @param c the char to find out
 * @return a pointer on the next node, nullptr if not found
 */
    AbstractNode* get_next(wchar_t c);

    ~HashNode();

};


#endif //FILLWORDSSOLVER_HASHNODE_H
