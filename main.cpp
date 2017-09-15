#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <iomanip>
#include <list>
#include "src/Trie.hpp"
#include "src/Nodes/HashNode.h"
#include "src/Solver.hpp"
#include "cwchar"

using namespace std;

locale ulocale(locale(),

new codecvt_utf8<wchar_t>);


clock_t start_time;

double sec(clock_t start, clock_t end)
{
    return double(end - start) / CLOCKS_PER_SEC;
}

double print_time(clock_t begin, clock_t end, string extra_output = "")
{
    double time = sec(begin, end);
    cout << setw(30) << extra_output << ":\t" << time << "\n";
    return time;
}


void tick()
{
    start_time = clock();
}

void tack(string out = "")
{
    print_time(start_time, clock(), out);
}

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

template<typename T>
void print_arr(std::vector<T> arr, unsigned int how_many = 5)
{
    if (how_many > arr.size())
        how_many = arr.size();
    std::wcout << "\n";
    for (T x: arr)
    {
        --how_many;
        std::wcout << x << " ";
        if (how_many == 0)
            break;
    }
}

/**
 * Returns seconds between the start and end.
 * @param start the start of the period
 * @param end the end of the period
 * @return secods within start and end
 */

/**
 * Tests a solver with the type of the node.
 * @tparam Node the type of the node of the trie
 * @param table the table of the game to check solver on
 * @param dict the dictionary to check the solver on
 * @param need_result do you need the solution printed?
 * @param need_stop do you need to stop befor the end of the test?
 */
template<typename HeadNode, typename OtherNode = HeadNode>
void TestSolver(const vector<vector<wchar_t>>& table,
                Solver<HeadNode, OtherNode> s,
                bool need_result = true, bool need_stop = false)
{
    clock_t program_started = clock();
    s.set_table(table);
    clock_t solving_started = clock();
    s.solve();
    auto result = s.get_solution();
    clock_t end = clock();
    double preparing_time = print_time(program_started, solving_started, "Calc neighbours time");
    double solving_time = print_time(solving_started, end, "Solving time");
    print_time(program_started, end, "Full time");

    if (need_result)
    {
        print_arr(result, result.size());
        cout << "\n";
    }

    if (need_stop)
    {
        wchar_t c;
        std::wcin >> c; // for pause and memory measurement
    }
}

const int MIN_WORD_LENGTH = 4;

template<typename HeadNode, typename OtherNode = HeadNode>
Solver<HeadNode, OtherNode> get_solver(vector<wstring> dict, int min_length = MIN_WORD_LENGTH)
{
    tick();
    auto res = Solver<HeadNode, OtherNode>(min_length, dict);
    tack("Solver (already read dict)");
    return res;
};

template<typename HeadNode, typename OtherNode = HeadNode>
Solver<HeadNode, OtherNode> get_solver(string dict_path, int min_length = MIN_WORD_LENGTH)
{
    tick();
    auto res = Solver<HeadNode, OtherNode>(min_length, dict_path);
    tack("Solver (dict reading)");
    return res;
};


int main(int argc, char** args)
{
    wcout.imbue(ulocale);


    string dictFile("../Dictionaries/dict.txt");
    string tableFile("../Tables/test_table.txt");

    const std::string shortened_dict_path = "../Dictionaries/shortened_dict.txt";
    if (argc == 3) // if the arguments specify the full_dict and table files
    {
        dictFile = args[1];
        tableFile = args[2];
    }

    // Measure the reading from file system.
    cout << "Table file: " << tableFile << "\n";
    tick();
    auto full_dict = read_dict(dictFile);
    tack("Dictionary reading");
    tick();
    auto table = read_table(tableFile);
    tack("Table reading");


    wcout << "Array node: " << endl;
    TestSolver(table, get_solver<ArrayNode>(full_dict));

//    wcout << "Array node: " << endl;
//    TestSolver(table, get_solver<ArrayNode>(shortened_dict_path));
//
//    wcout << "List node: " << endl;
//    TestSolver(table, get_solver<ListNode>(full_dict));
//
//    wcout << "List node: " << endl;
//    TestSolver(table, get_solver<ListNode>(shortened_dict_path));
//
//    wcout << "Hash node: " << endl;
//    TestSolver(table, get_solver<HashNode>(full_dict));
//
//    wcout << "Hash node: " << endl;
//    TestSolver(table, get_solver<HashNode>(shortened_dict_path));
//
//    wcout << "List-Array nodes: " << endl;
//    TestSolver(table, get_solver<ListNode, ArrayNode>(full_dict));
//
//    wcout << "List-Array nodes: " << endl;
//    TestSolver(table, get_solver<ListNode, ArrayNode>(shortened_dict_path));
//
//    wcout << "Array-List nodes: " << endl;
//    TestSolver(table, get_solver<ArrayNode, ListNode>(full_dict));
//
//    wcout << "Array-List nodes: " << endl;
//    TestSolver(table, get_solver<ArrayNode, ListNode>(shortened_dict_path));

    return 0;
}