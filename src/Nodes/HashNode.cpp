//
// Created by Air_R on 05.04.17.
//

#include "HashNode.h"

void HashNode::add_edge(wchar_t value, AbstractNode* next)
{
    _edges.insert(std::make_pair(value, Edge(value, next)));
}


AbstractNode* HashNode::get_next(wchar_t c)
{
//    for (Edge e: _edges)
//    {
//        if (e.get_value() == c)
//            return (ListNode*) e.get_next();
//    }

    auto it = _edges.find(c);
    if (it == _edges.end())
        return nullptr;

    return it->second.get_next();
}

HashNode::~HashNode()
{
    _edges.clear();
    //delete _edges;
//    for (Edge e: _edges)
//    {
//        delete e.get_next();
//    }
}