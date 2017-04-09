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

template<typename HeadNode, typename OtherNode>
Trie<HeadNode, OtherNode>::Trie(std::string& file_path)
{
    create_true_from_file(file_path);
}

template<typename HeadNode, typename OtherNode>
void Trie<HeadNode, OtherNode>::create_true_from_file(std::string& path)
{
    //std::cout << "Inside of Trie<HeadNode, OtherNode>::create_true_from_file";
    _head = new HeadNode(nullptr);
    _iter = _head;
    AbstractNode* iter;

    using namespace std;
    std::wifstream in(path);
    locale ulocale(locale(),
    new codecvt_utf8<wchar_t>);
    in.imbue(ulocale);
    wcout.imbue(ulocale);

    short steps_back, depth = 0;
    std::wstring word;

    iter = _head;

    AbstractNode* nodes[30];
    nodes[0] = _head;

    while (in.good())
    {
        in >> steps_back >> word;

        //std::wcout << '\n' << steps_back << L" " << word << L" " << depth;

        depth -= (steps_back);
        iter = nodes[depth];
//
//        while (steps_back)
//        {
//            --steps_back;
//            //--depth;
//            iter = iter->get_prev();
//        }

        for (wchar_t c: word)
        {
            AbstractNode* next = iter->get_next(c);

            if (next == nullptr)
            {
                next = new OtherNode(iter);
                iter->add_edge(c, next);
            }

            iter = next;
            ++depth;
            nodes[depth] = iter;
        }
        iter->make_leaf();
    }
}