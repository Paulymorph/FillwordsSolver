//
// Created by Air_R on 04.04.17.
//

#ifndef FILLWORDSSOLVER_SOLVER_H
#define FILLWORDSSOLVER_SOLVER_H

#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <iostream>
#include <codecvt>
#include <set>

#include "Trie.h"
#include "Nodes/ArrayNode.h"
#include "Nodes/ListNode.h"
#include "Nodes/HashNode.h"

typedef std::map<std::wstring, int> dict_type;
typedef dict_type::iterator map_iter_type;
typedef std::vector<wchar_t> table_row_type;
typedef Trie<ListNode> TrieType;
//typedef Trie<ListNode> TrieType;
//typedef Trie<HashNode> TrieType;
//typedef Trie<ArrayNode> TrieType;

template<typename HeadNode, typename OtherNode = HeadNode>
class Solver
{
    TrieType trie;

    std::vector<table_row_type> _table;
    std::vector<std::wstring> _all_found_words;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> neighbours;
    int table_size = -1;
    int min_length;


    void generate_neighbours()
    {
        neighbours.clear();
        neighbours.reserve(table_size);
        for (int i = 0; i < table_size; ++i)
        {
            std::vector<std::vector<std::pair<int, int>>> tmp_arr;
            for (int j = 0; j < table_size; ++j)
                tmp_arr.push_back(get_neighbours(i, j));
            neighbours.push_back(tmp_arr);
        }
    }

    std::vector<std::pair<int, int>> get_neighbours(const int& x, const int& y)
    {
        //std::cout << "input coor " <<  x << ' ' << y << "\n\t\t";
        std::vector<std::pair<int, int>> coor;
        if (x > 0)
            coor.push_back(std::pair<int, int>(x - 1, y));
        if (x < table_size - 1)
            coor.push_back(std::pair<int, int>(x + 1, y));
        if (y > 0)
            coor.push_back(std::pair<int, int>(x, y - 1));
        if (y < table_size - 1)
            coor.push_back(std::pair<int, int>(x, y + 1));
//        for (int i = x - 1; i <= x + 1; ++i)
//            for (int j = y - 1; j <= y + 1; ++j)
//                if (((i == x) ^ (j == y)) && is_that_possible_coor(i, j))
//                    coor.push_back(std::pair<int, int>(i, j));
        return coor;
    }


    inline bool is_full_word(const std::wstring& str)
    {
        return trie.is_in_leaf();
    }

    void
    try_to_find_word(std::vector<std::vector<bool>>& visited, std::wstring already_in_word, int& x, int& y, int depth)
    {
        if (depth >= min_length && is_full_word(already_in_word))
            _all_found_words.push_back(already_in_word);

        if (!trie.move_along(_table[x][y]))
            return;

        visited[x][y] = true;

        for (std::pair<int, int> c: neighbours[x][y])
            if (!visited[c.first][c.second])
                try_to_find_word(visited, already_in_word + _table[x][y], c.first, c.second, depth + 1);

        visited[x][y] = false;
        trie.reset_iter();
    }

    std::vector<std::vector<bool>> get_zero_matrix(int size)
    {
        return std::vector<std::vector<bool>>(table_size, std::vector<bool>(table_size, false));
    }

public:

    Solver(int min, std::string dict_path) : trie(dict_path), min_length(min)
    {

    }

    Solver(int min, std::vector<std::wstring> dict) : trie(dict), min_length(min)
    {
        min_length = min;
    }


    void set_table(std::vector<table_row_type> table)
    {
        _table = table;
        table_size = table.size();
        generate_neighbours();
    }


    void solve()
    {
        _all_found_words.clear();
        auto zero_matr = get_zero_matrix(table_size);
        for (int i = 0; i < table_size; ++i)
        {
            for (int j = 0; j < table_size; ++j)
            {
                std::wstring tmp_str = std::wstring();
                std::vector<std::vector<bool>> tmp_matr = zero_matr;
                try_to_find_word(tmp_matr, tmp_str, i, j, 0);
                //std::cout << i << " " << j << " " << _all_found_words.size() << "\n";
            }
        }

        std::set<std::wstring> s(_all_found_words.begin(), _all_found_words.end());
        _all_found_words.assign(s.begin(), s.end());
        std::sort(_all_found_words.begin(), _all_found_words.end());
    }

    std::vector<std::wstring> get_solution()
    {
        return _all_found_words;
    }
};


#endif //FILLWORDSSOLVER_SOLVER_H