//
// Created by Paul Danilin on 06/04/2017.
//

#include "TestListNode.h"
#include "../Utilities.h"

void TestListNode::add_edge(wchar_t value, AbstractNode* next)
{
    is_such_next[hash(value, TestListNode::ALPHABET_SIZE)] = true;
    _edges.push_front(Edge(value, next));
}

AbstractNode* TestListNode::get_next(wchar_t c)
{
    if (!is_such_next[hash(c, TestListNode::ALPHABET_SIZE)])
        return nullptr;

    for (Edge e: _edges)
    {
        if (e.get_value() == c)
            return e.get_next();
    }

    return nullptr;
}

TestListNode::~TestListNode()
{
    for (Edge e: _edges)
    {
        delete e.get_next();
    }
}