#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <iomanip>
#include "Trie.hpp"
#include "ArrayNode.h"
#include "Solver.cpp"

using namespace std;

locale ulocale(locale(),

new codecvt_utf8<wchar_t>);

vector<wstring> read_dict(string file_name)
{
    wifstream input(file_name, wifstream::in);
    // Hope, the magic helps.
    input.imbue(ulocale);

    vector<wstring> dict;
    while (!input.eof())
    {
        wstring word;
        getline(input, word);
        dict.push_back(word);
    }

    dict.shrink_to_fit();
    return dict;
}

void Test()
{
    Trie<ArrayNode> t({L"абвя", L"воарл"});
    wcout << t.is_in_leaf() << endl;
    wcout << t.move_along(L'а') << endl;
    wcout << t.move_along(L'б') << endl;
    wcout << t.move_along(L'в') << endl;
    wcout << t.move_along(L'я') << endl;
    wcout << t.is_in_leaf() << endl;
    wcout << t.move_along(L'а') << endl;

    t = Trie<ArrayNode>(read_dict("../dict.txt"));
}

/**
 * Reads the char table from the file.
 * @param file_name the name of the file to read from
 * @return the char table read.
 */
vector<vector<wchar_t>> read_table(string file_name)
{
    wifstream input(file_name, wifstream::in);
    // Hope, the magic helps.
    input.imbue(ulocale);

    int size;
    input >> size;

    vector<vector<wchar_t>> table;
    table.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        table.push_back(vector<wchar_t>());
        table.back().reserve(size);
        for (int j = 0; j < size; ++j)
        {
            wchar_t ch;
            input >> ch;
            table.back().push_back(ch);
//            wcout << ch << " "; // testing
        }
//        wcout << endl; // testing
    }

    input.close();
    return table;
}

template<typename T>
void print_arr(std::vector<T> arr, int how_many = 5)
{
    if (how_many > arr.size())
        how_many = arr.size();
    for (T x: arr)
    {
        --how_many;
        std::wcout << x << ' ';
        if (how_many == 0)
            break;
    }
    wcout << endl;
}

double sec(clock_t start, clock_t end)
{
    return double(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char** args)
{
    string dictFile("../dictFile.txt");
    string tableFile("../table2.txt");
    if (argc == 3)
    {
        dictFile = args[1];
        tableFile = args[2];
        wcout << wstring(dictFile.begin(), dictFile.end()) << " "
              << wstring(tableFile.begin(), tableFile.end()) << endl;
    }

    clock_t reading_start = clock();
    auto dictionary = read_dict(dictFile);
    auto table = read_table(tableFile);
    clock_t reading_end = clock();
    std::cout << std::setw(20) << "Reading time: \t" << sec(reading_start, reading_end) << "\n";

    clock_t program_started = clock();
    wcout.imbue(ulocale);

    Solver s(4, 15, dictionary);
    s.set_table(table);
    clock_t solving_started = clock();
    s.solve();
    auto result = s.get_solution();
    clock_t end = clock();
    double preparing_time = double(solving_started - program_started) / CLOCKS_PER_SEC;
    double solving_time = double(end - solving_started) / CLOCKS_PER_SEC;
    std::cout << std::setw(20) << "Preparation time: \t" << sec(program_started, solving_started) << "\n";
    std::cout << std::setw(20) << "Solving time: \t" << sec(solving_started, end) << "\n";
    std::cout << std::setw(20) << "Full time: \t" << preparing_time + solving_time << "\n";
    print_arr(result, result.size());
    return 0;
}