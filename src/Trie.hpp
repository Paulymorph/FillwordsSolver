//
// Created by Paul Danilin on 04/04/2017.
//

#include "Trie.h"

template<typename HeadNode, typename OtherNode>
Trie<HeadNode, OtherNode>::Trie(const std::vector<std::wstring>& words)
{
    _head = new HeadNode(nullptr);
    _iter = _head;
    AbstractNode* iter;
    for (std::wstring word: words)
    {
        iter = _head;
        for (wchar_t c: word)
        {
            AbstractNode* next = iter->get_next(c);

            if (next == nullptr)
            {
                next = new OtherNode(iter);
                iter->add_edge(c, next);
            }

            iter = next;
        }
        iter->make_leaf();
    }
}

template<typename HeadNode, typename OtherNode>
bool Trie<HeadNode, OtherNode>::move_along(wchar_t c)
{
    AbstractNode* next = _iter->get_next(c);

    if (next == nullptr)
        return false;

    _iter = next;
    return true;
}

template<typename HeadNode, typename OtherNode>
bool Trie<HeadNode, OtherNode>::is_in_leaf()
{
    return _iter->is_leaf();
}

template<typename HeadNode, typename OtherNode>
void Trie<HeadNode, OtherNode>::reset_iter()
{
    _iter = _iter->get_prev();
}