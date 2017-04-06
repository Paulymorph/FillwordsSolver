#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <iomanip>

#include "src/Trie.hpp"
#include "src/Solver.cpp"

// NODES
#include "src/Nodes/STL_ArrayNode.h"
#include "src/Nodes/ArrayNode.h"
#include "src/Nodes/ListNode.h"
#include "src/Nodes/HashNode.h"

using namespace std;

locale ulocale(locale(),

new codecvt_utf8<wchar_t>);

/**
 * Reads the dictionary (each line is a word).
 * @param file_name the file containing the dictionary
 * @return the read words
 */
vector<wstring> read_dict(string file_name)
{
    wifstream input(file_name, wifstream::in);

    if (!input.good())
        throw std::logic_error("Error reading " + file_name);

    // Hope, the magic helps to correctly read .
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

void SimpleTrieTest()
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

    if (!input.good())
        throw std::logic_error("Error reading " + file_name);

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
        }
    }

    input.close();
    return table;
}

/**
 * Prints out the first how_many elements of the array.
 * @tparam T
 * @param arr
 * @param how_many
 */
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

/**
 * Returns seconds between the start and end.
 * @param start the start of the period
 * @param end the end of the period
 * @return secods within start and end
 */
double sec(clock_t start, clock_t end)
{
    return double(end - start) / CLOCKS_PER_SEC;
}

/**
 * Tests a solver with the type of the node.
 * @tparam Node the type of the node of the trie
 * @param table the table of the game to check solver on
 * @param dict the dictionary to check the solver on
 * @param need_result do you need the solution printed?
 * @param need_stop do you need to stop befor the end of the test?
 */
template<typename HeadNode, typename OtherNode = HeadNode>
void TestSolver(const vector<vector<wchar_t>>& table, const vector<wstring>& dict,
                bool need_result = false, bool need_stop = false)
{
    clock_t program_started = clock();
    Solver<HeadNode, OtherNode> s(4, 15, dict);;
    s.set_table(table);
    clock_t solving_started = clock();
    s.solve();
    auto result = s.get_solution();
    clock_t end = clock();
    double preparing_time = double(solving_started - program_started) / CLOCKS_PER_SEC;
    double solving_time = double(end - solving_started) / CLOCKS_PER_SEC;
    wcout << setw(20) << "Preparation time: \t" << sec(program_started, solving_started) << "\n";
    wcout << setw(20) << "Solving time: \t" << sec(solving_started, end) << "\n";
    wcout << setw(20) << "Full time: \t" << preparing_time + solving_time << "\n";

    if (need_result)
        print_arr(result, result.size());

    if (need_stop)
    {
        wchar_t c;
        std::wcin >> c; // for pause and memory measurement
    }
}

int main(int argc, char** args)
{
    wcout.imbue(ulocale);

    string dictFile("../Dictionaries/dict.txt");
    string tableFile("../Tables/table2.txt");
    if (argc == 3) // if the arguments specify the dictionary and table files
    {
        dictFile = args[1];
        tableFile = args[2];
    }

    // Measure the reading from file system.
    clock_t reading_start = clock();
    auto dictionary = read_dict(dictFile);
    auto table = read_table(tableFile);
    clock_t reading_end = clock();
    std::wcout << std::setw(20) << "Reading time: \t" << sec(reading_start, reading_end) << "\n";

    wcout << "Array node: " << endl;
    TestSolver<ArrayNode>(table, dictionary);

    wcout << "STL array node: " << endl;
    TestSolver<STL_ArrayNode>(table, dictionary);

    wcout << "List node: " << endl;
    TestSolver<ListNode>(table, dictionary);

    wcout << "Hash node: " << endl;
    TestSolver<HashNode>(table, dictionary);

    wcout << "Mix nodes: " << endl;
    TestSolver<ArrayNode, ListNode>(table, dictionary);

    return 0;
}
