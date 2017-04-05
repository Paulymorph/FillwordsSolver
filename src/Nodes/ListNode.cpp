//
// Created by Paul Danilin on 04/04/2017.
//

#include "ListNode.h"

void ListNode::add_edge(wchar_t value, AbstractNode* next)
{
    _edges.push_front(Edge(value, next));
}

AbstractNode* ListNode::get_next(wchar_t c)
{
    for (Edge e: _edges)
    {
        if (e.get_value() == c)
            return (ListNode*) e.get_next();
    }

    return nullptr;
}

ListNode::~ListNode()
{
    for (Edge e: _edges)
    {
        delete e.get_next();
    }
}