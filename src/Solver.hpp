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
#include "WordWithCoors.h"

typedef std::map<std::wstring, int> dict_type;
typedef dict_type::iterator map_iter_type;
typedef std::vector<wchar_t> table_row_type;

template<typename HeadNode, typename OtherNode = HeadNode>
class Solver
{
    Trie<HeadNode, OtherNode> trie;

    std::vector<table_row_type> _table;
    std::vector<WordWithCoors> _all_found_words;
    std::vector<std::vector<std::vector<Point>>> neighbours;
    int table_size = -1;
    int min_length;

    int MAX_WORD_LENGTH = 30;


    void generate_neighbours()
    {
        neighbours.clear();
        neighbours.reserve(table_size);
        for (int i = 0; i < table_size; ++i)
        {
            std::vector<std::vector<Point>> tmp_arr;
            for (int j = 0; j < table_size; ++j)
                tmp_arr.push_back(get_neighbours(i, j, table_size));
            neighbours.push_back(tmp_arr);
        }
    }

    inline bool is_full_word()
    {
        return trie.is_in_leaf();
    }

    void
    try_to_find_word(bool** visited, wchar_t* already_in_word, std::vector<Point> word_coors, const int& x,
                     const int& y,
                     int depth)
    {
        if (visited[x][y])
            return;

        if (depth >= min_length && is_full_word())
        {
            // save solution
            WordWithCoors tmp_res(std::wstring(already_in_word, depth),
                                  std::vector<Point>(word_coors.begin(), word_coors.begin() + depth));
//            tmp_res.word = std::wstring(already_in_word, depth);
//            tmp_res.coors = std::vector<Point>(word_coors.begin(), word_coors.begin() + depth);
            _all_found_words.push_back(tmp_res);
        }


        if (!trie.move_along(_table[x][y]))
            return;

        visited[x][y] = true;
        already_in_word[depth] = _table[x][y];
        word_coors[depth] = Point(x, y, table_size);
        ++depth;

        for (Point& c: neighbours[x][y])
            try_to_find_word(visited, already_in_word, word_coors, c.x, c.y, depth);

        visited[x][y] = false;
        trie.reset_iter();
    }

    std::vector<std::vector<bool>> get_zero_matrix(int size)
    {
        return std::vector<std::vector<bool>>(table_size, std::vector<bool>(table_size, false));
    }

    void sort_results()
    {
        std::set<WordWithCoors> s(_all_found_words.begin(), _all_found_words.end());
        _all_found_words.assign(s.begin(), s.end());
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
//        auto zero_matr = get_zero_matrix(table_size);

        bool** zero_matr = new bool* [table_size];
        for (int i = 0; i < table_size; ++i)
        {
            zero_matr[i] = new bool[table_size];
            for (int j = 0; j < table_size; ++j)
                zero_matr[i][j] = false;
        }

        int tmp_depth_value = 0;
        wchar_t* tmp_recurs_call_chars = new wchar_t[MAX_WORD_LENGTH];
        std::vector<Point> tmp_word_coors(MAX_WORD_LENGTH);

        for (int i = 0; i < table_size; ++i)
            for (int j = 0; j < table_size; ++j)
                try_to_find_word(zero_matr, tmp_recurs_call_chars, tmp_word_coors, i, j, tmp_depth_value);


        delete[] tmp_recurs_call_chars;
        for (int i = 0; i < table_size; ++i)
            delete[] zero_matr[i];
        delete[] zero_matr;


        sort_results();
//        for (auto& el: _all_found_words)
//            std::wcout << el.word << L", ";
        std::wcout << L"\n";

    }

    std::vector<WordWithCoors> get_solution()
    {
        return _all_found_words;
    }

    void print_results()
    {
        for (auto& el: _all_found_words)
            el.print();
    }
};


#endif //FILLWORDSSOLVER_SOLVER_H