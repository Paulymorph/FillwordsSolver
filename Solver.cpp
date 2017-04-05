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
#include "ArrayNode.h"
#include "ListNode.h"
#include "HashNode.h"

typedef std::map<std::wstring, int> dict_type;
typedef dict_type::iterator map_iter_type;
typedef std::vector<wchar_t> table_row_type;
//typedef Trie<ListNode> TrieType;
//typedef Trie<HashNode> TrieType;
typedef Trie<ArrayNode> TrieType;

class Solver
{
    TrieType trie;

    std::vector<table_row_type> _table;
    std::vector<std::wstring> _all_found_words;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> neighbours;
    int table_size = -1;
    int min_length, max_length;

//    inline bool is_that_possible_coor(const int& i, const int& j)
//    {
//        return i >= 0 && j >= 0 && i < table_size && j < table_size;
//    }


    void generate_neighbours()
    {
        neighbours.clear();
        neighbours.reserve(table_size);
        for (int i = 0; i < table_size; ++i)
        {
            std::vector<std::vector<std::pair<int, int>>> tmp_arr;
            for (int j = 0; j < table_size; ++j)
            {
                tmp_arr.push_back(get_neighbours(i, j));
//                std::cout << i << " " << j << "\n";
//                for (auto x: tmp_arr[tmp_arr.size() - 1])
//                    std::cout << "\t" << x.first << " " << x.second << "\n";
            }
            neighbours.push_back(tmp_arr);
        }

//        for (int i = 0; i < table_size; ++i)
//
//            for (int j = 0; j < table_size; ++j)
//            {
//                std::cout << i << " " << j << "\n";
//                for (auto x: neighbours[i][j])
//                    std::cout << "\t" << x.first << " " << x.second << "\n";
//            }

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
    try_to_find_word(std::vector<std::vector<bool>>& visited,
                     std::wstring already_in_word, int& x, int& y, unsigned int depth)
    {
        if (depth >= min_length && is_full_word(already_in_word))
            _all_found_words.push_back(already_in_word);

        if (!trie.move_along(_table[x][y]))
            return;

        if (depth > max_length)
        {
            trie.reset_iter();
            return;
        }

        visited[x][y] = true;

        for (std::pair<int, int> c: neighbours[x][y])
        //for (std::pair<int, int> c: get_neighbours(x, y))
            if (!visited[c.first][c.second])
                try_to_find_word(visited, already_in_word + _table[x][y], c.first, c.second, depth + 1);

        visited[x][y] = false;
        trie.reset_iter();
    }

    std::vector<std::vector<bool>> get_zero_matrix(int size)
    {
        std::vector<std::vector<bool>> arr;
        for (int i = 0; i < table_size; ++i)
        {
            arr.push_back(std::vector<bool>(table_size, false));
        }
        return arr;
    }


    void delete_substring()
    {
        for (int i = 0; i < _all_found_words.size(); ++i)
        {
            for (int j = 0; j < _all_found_words.size(); ++j)
            {
                if (i != j)
                    if (_all_found_words[i].find(_all_found_words[j]) != std::string::npos)
                    {
                        _all_found_words.erase(_all_found_words.begin() + j);
                        --j;
                        if (i >= j)
                            --i;
                    }
            }

        }
    }

public:

    Solver(int min, int max, std::vector<std::wstring> dict) : trie(dict)
    {
        min_length = min;
        max_length = max;
    }

    void set_table(std::vector<table_row_type> table)
    {
        //_table.insert(_table.end(), table.begin(), table.end());
        _table = table;
        table_size = table.size();
        generate_neighbours();
    }

    void set_dict(std::vector<std::wstring> dict)
    {
        trie = TrieType(dict);
    }

    void print_dict(dict_type& dict, int how_many = 10)
    {
        std::cout << '\n';
        for (auto x: dict)
        {
            --how_many;
            std::wcout << x.first << "  " << x.second << '\n';
            if (!how_many)
                break;
        }
        std::cout << '\n';
    }

    void solve()
    {
        _all_found_words.clear();
        for (int i = 0; i < table_size; ++i)
        {
            for (int j = 0; j < table_size; ++j)
            {
                std::wstring tmp_str = std::wstring();
                std::vector<std::vector<bool>> tmp_matr = get_zero_matrix(table_size);
                try_to_find_word(tmp_matr, tmp_str, i, j, 0);
                //std::cout << i << " " << j << " " << _all_found_words.size() << "\n";
            }
        }

        std::set<std::wstring> s(_all_found_words.begin(), _all_found_words.end());
        _all_found_words.assign(s.begin(), s.end());
        //delete_substring();
        std::sort(_all_found_words.begin(), _all_found_words.end());
    }

    std::vector<std::wstring> get_solution()
    {
        return _all_found_words;
    }


};


#endif //FILLWORDSSOLVER_SOLVER_H
