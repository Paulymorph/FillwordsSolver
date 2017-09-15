//
// Created by Air_R on 15/09/17.
//

#pragma once

#include <string>
#include <vector>
#include "Point.hpp"

class WordWithCoors
{
    std::set<Point> coors;
    std::wstring word;
public:

    WordWithCoors(std::wstring word, std::vector<Point> coors)
    {
        this->word = word;
        this->coors = std::set<Point>(coors.begin(), coors.end());
    }


    friend bool operator <(const WordWithCoors& c1, const WordWithCoors& c2)
    {
        return c1.word == c2.word ? c1.coors < c2.coors : c1.word < c2.word;
    }

    void print()
    {
        std::wcout << this;
    }

    friend std::wostream& operator <<(std::wostream& stream, const WordWithCoors& item)
    {
        stream << std::setw(15) << item.word << " ";
        for (const Point& p: item.coors)
            stream << "(" << p.x << ", " << p.y << "), ";
        stream << "\n";
        return stream;
    }

};