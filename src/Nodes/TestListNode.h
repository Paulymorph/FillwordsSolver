//
// Created by Paul Danilin on 06/04/2017.
//

#ifndef FILLWORDSSOLVER_TESTLISTNODE_H
#define FILLWORDSSOLVER_TESTLISTNODE_H

#include <forward_list>
#include <bitset>
#include "../Edge.h"

class TestListNode : public AbstractNode
{
    static const size_t ALPHABET_SIZE = 32;
    std::forward_list<Edge> _edges;
    std::bitset<TestListNode::ALPHABET_SIZE> is_such_next;
public:
    TestListNode(AbstractNode* prev)
    { this->_prev = prev; }

    void add_edge(wchar_t value, AbstractNode* next);

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    AbstractNode* get_next(wchar_t c);

    ~TestListNode();
};


#endif //FILLWORDSSOLVER_TESTLISTNODE_H
