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

template<typename HeadNode, typename OtherNode = HeadNode>
class Solver
{
    Trie<HeadNode, OtherNode> trie;

    std::vector<table_row_type> _table;
    std::vector<std::wstring> _all_found_words;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> neighbours;
    int table_size = -1;
    int min_length;

    int MAX_WORD_LENGTH = 30;


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
        return coor;
    }

    inline bool is_full_word()
    {
        return trie.is_in_leaf();
    }

    wchar_t* tmp_recurs_call_chars = new wchar_t[MAX_WORD_LENGTH];

    int super_depth = 0;

    std::wstring words[16];

    void
    try_to_find_word(bool** visited, int visited_count, const int& x, const int& y,
                     int depth)
    {
        // All table symbols are chosen already
        if (visited_count == table_size * table_size)
        {
//            std::wcout << L"All cells are chosen. Visited count: " << visited_count << ", words: ";
//            for (int i = _all_found_words.size() - super_depth - 1; i < _all_found_words.size(); ++i)
//                std::wcout << _all_found_words[i] << ", ";

//            for (int i = 0; i < super_depth; ++i)
//                std::wcout << words[i] << " ";
//
//            std::wcout << std::wstring(tmp_recurs_call_chars, depth);

//            for (int k = 0; k < table_size; ++k)
//            {
//                std::cout << "\n";
//                for (int i = 0; i < table_size; ++i)
//                {
//                    std::cout << visited[k][i] << " ";
//                }
//            }

//            std::cout << << "\n";
            return;
        }


        if (visited[x][y])
            return;

//        std::wcout << x << L" " << y << L" " << depth << L" " << tmp_recurs_call_chars << L"\n";


//        std::wcout << " <<<*\n";


        if (depth >= min_length && is_full_word())
        {
            // save solution
            std::wstring tmp_word(tmp_recurs_call_chars, depth);
//            _all_found_words.push_back(tmp_word);
//            std::wcout << L"\nNew word: " << tmp_word << ", super_depth: " << super_depth << L"\n";

            words[super_depth] = tmp_word;
            ++super_depth;

//            std::cout << "visited_count " << visited_count << "\n";

            AbstractNode* tmp_node = this->trie.get_iter();
            trie.start_new_word();

            // start recursive solving
            for (int i = 0, zero = 0; i < table_size; ++i)
                for (int j = 0; j < table_size; ++j)
                    // depth should be zero, because new word is searched
                {
//                        printf("\nEntering into recursion\n");
                    try_to_find_word(visited, visited_count, i, j, zero);
                }

            trie.set_iter(tmp_node);
            --super_depth;

//            tmp_recurs_call_chars[depth]

//            for (int i = 0; i < MAX_WORD_LENGTH; ++i)
//                tmp_recurs_call_chars[i] = L'*';

            // 'tmp_recurs_call_chars' was overwriten, so return it previous value
//            for (int i = 0; i < depth; ++i)
//                tmp_recurs_call_chars[i] = tmp_word[i];
        }


        if (!trie.move_along(_table[x][y]))
            return;


        visited[x][y] = true;
        tmp_recurs_call_chars[depth] = _table[x][y];
        ++depth;
        ++visited_count;

        for (std::pair<int, int> c: neighbours[x][y])
            try_to_find_word(visited, visited_count, c.first, c.second, depth);

        --depth;
        --visited_count;
        visited[x][y] = false;
        trie.reset_iter();
    }

    std::vector<std::vector<bool>> get_zero_matrix(int size)
    {
        return std::vector<std::vector<bool>>(table_size, std::vector<bool>(table_size, false));
    }

    void sort_results()
    {
        std::set<std::wstring> s(_all_found_words.begin(), _all_found_words.end());
        _all_found_words.assign(s.begin(), s.end());
        std::sort(_all_found_words.begin(), _all_found_words.end());
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

//        auto zero_matr = get_zero_matrix(table_size);
        bool** zero_matr = new bool* [table_size];
        for (int i = 0; i < table_size; ++i)
        {
            zero_matr[i] = new bool[table_size];
            for (int j = 0; j < table_size; ++j)
                zero_matr[i][j] = false;
        }
        int tmp_depth_value = 0;
        for (int i = 0; i < table_size; ++i)
            for (int j = 0; j < table_size; ++j)
        {
            _all_found_words.clear();
            try_to_find_word(zero_matr, 0, i, j, tmp_depth_value);
            std::wcout << i << L" " << j << L": ";
            for (int k = 0; k < super_depth; ++k)
                std::wcout << words[k] << " ";


//            sort_results();
//            for (std::wstring el: _all_found_words)
//                std::wcout << el << L", ";
//            std::wcout << words;
            std::wcout << L"\n";
        }

        sort_results();

        for (int i = 0; i < table_size; ++i)
            delete[] zero_matr[i];
        delete[] zero_matr;

    }

    std::vector<std::wstring> get_solution()
    {
        return _all_found_words;
    }


    ~Solver()
    {
        if (tmp_recurs_call_chars)
            delete[] tmp_recurs_call_chars;
    }
};


#endif //FILLWORDSSOLVER_SOLVER_H