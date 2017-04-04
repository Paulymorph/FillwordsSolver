//
// Created by Paul Danilin on 04/04/2017.
//

#include "Trie.h"

template<typename Node>
Trie<Node>::Trie(std::vector<std::string> words)
{
    _head = new Node();
    _iter = _head;
    Node* iter;
    for (std::string word: words)
    {
        iter = _head;
        for (char c: word)
        {
            Node* next = (Node*) iter->get_next(c);

            if (next == nullptr)
            {
                next = new Node();
                iter->add_edge(c, next);
            }

            iter = next;
        }
        iter->make_leaf();
    }
}

template<typename Node>
bool Trie<Node>::move_along(char c)
{
    Node* next = (Node*) _iter->get_next(c);

    if (next == nullptr)
        return false;
    _iter = next;
    return true;
}

template<typename Node>
bool Trie<Node>::is_in_leaf()
{
    return _iter->is_leaf();
}

template<typename Node>
void Trie<Node>::reset_iter()
{ _iter = _head; }