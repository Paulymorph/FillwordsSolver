//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_TRIE_H
#define FILLWORDSSOLVER_TRIE_H

#include <forward_list>
#include <vector>
#include <string>

//#include "Node.h"

template<typename Node>
class Trie
{
    Node* _head;
    Node* _iter;

public:
    /**
     * Constructs a trie on the array of words.
     * @param words
     */
    Trie(const std::vector<std::wstring>& words);

    /**
     * Tries to move from the current position to the new along the char.
     * @param c the char to move along
     * @return true if successful, false otherwise. If the edge doesn't exist, the iterator doesn't change.
     */
    bool move_along(wchar_t c);

    /**
     * Checks if the iterator in the current position is in a leaf.
     * @return true if in a leaf, false otherwise
     */
    bool is_in_leaf();

    /**
     * Resets the iterator of the tree.
     */
    void reset_iter();

    ~Trie()
    { delete _head; }
};

#endif //FILLWORDSSOLVER_TRIE_H
