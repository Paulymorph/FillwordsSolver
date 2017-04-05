//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_NODE_H
#define FILLWORDSSOLVER_NODE_H

#include "../Edge.h"

#include <forward_list>

class ListNode : public AbstractNode
{
    std::forward_list<Edge> _edges;
public:
    ListNode(AbstractNode* prev)
    { this->_prev = prev; }

    void add_edge(wchar_t value, AbstractNode* next);

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    AbstractNode* get_next(wchar_t c);

    ~ListNode();
};


#endif //FILLWORDSSOLVER_NODE_H
