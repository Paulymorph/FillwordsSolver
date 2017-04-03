//
// Created by Paul Danilin on 04/04/2017.
//

#include "Trie.h"

Trie::Trie(std::vector<std::string> words)
{
    Node* iter;
    for (auto word = words.begin(); word != words.end(); word++)
    {
        iter = _head;
        for (auto c = word->begin(); c != word->end(); c++)
        {
            Node* next = iter->get_next(*c);

            if (next == nullptr)
            {
                next = new Node();
                iter->add_edge(*c, next);
            }

            iter = next;
        }
    }
}

bool Trie::move_along(char c)
{
    Node* next = _iter->get_next(c);

    if (next == nullptr)
        return false;
    _iter = next;
    return true;
}

bool Trie::is_in_leaf()
{
    return _iter->is_leaf();
}

void Trie::reset_iter()
{ _iter = _head; }