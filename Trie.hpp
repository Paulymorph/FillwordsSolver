//
// Created by Paul Danilin on 04/04/2017.
//

#include "Trie.h"

template<typename Node>
Trie<Node>::Trie(std::vector<std::wstring> words)
{
    _head = new Node(nullptr);
    _iter = _head;
    Node* iter;
    for (std::wstring word: words)
    {
        iter = _head;
        for (wchar_t c: word)
        {
            Node* next = (Node*) iter->get_next(c);

            if (next == nullptr)
            {
                next = new Node(iter);
                iter->add_edge(c, next);
            }

            iter = next;
        }
        iter->make_leaf();
    }
}

template<typename Node>
bool Trie<Node>::move_along(wchar_t c)
{
    Node* next = (Node*) _iter->get_next(c);

    if (next == nullptr)
        return false;

    str += c;

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
{
    str = str.substr(0, str.length() - 1);
    _iter = (Node*) _iter->get_prev();
}