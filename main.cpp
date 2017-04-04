#include <iostream>
#include <fstream>
#include <codecvt>
#include "Trie.hpp"
#include "ArrayNode.h"

void Test()
{
    Trie<ArrayNode> t({L"абв", L"воарл"});
    std::cout << t.is_in_leaf() << std::endl;
    std::cout << t.move_along(L'а') << std::endl;
    std::cout << t.move_along(L'б') << std::endl;
    std::cout << t.move_along(L'в') << std::endl;
    std::cout << t.is_in_leaf() << std::endl;
    std::cout << t.move_along(L'а') << std::endl;
}

/**
 * Reads the char table from the file.
 * @param file_name the name of the file to read from
 * @return the char table read.
 */
std::vector<std::vector<wchar_t>> read_table(std::string file_name)
{
    std::wifstream input(file_name, std::wifstream::in);

    int size;
    input >> size;

    // Hope, the magic helps.
    std::locale ulocale(std::locale(),
    new std::codecvt_utf8<wchar_t>);
    input.imbue(ulocale);

    std::vector<std::vector<wchar_t>> table;

    table.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        table.push_back(std::vector<wchar_t>());
        table.back().reserve(size);
        for (int j = 0; j < size; ++j)
        {
            wchar_t ch;
            input >> ch;
            table.back().push_back(ch);
        }
    }

    input.close();
    return table;
}

int main()
{
//    Test();
    auto a = read_table("../test_table.txt");
    return 0;
}