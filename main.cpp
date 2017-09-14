#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <iomanip>
#include <list>
#include "src/Trie.hpp"
#include "src/Nodes/HashNode.h"
#include "src/Solver.cpp"

using namespace std;

locale ulocale(locale(),

new codecvt_utf8<wchar_t>);

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
    for (T x: arr)
    {
        --how_many;
        std::wcout << x << ' ';
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
double sec(clock_t start, clock_t end)
{
    return double(end - start) / CLOCKS_PER_SEC;
}

double print_time(clock_t begin, clock_t end, string extra_output = "")
{
    double time = sec(begin, end);
    cout << setw(20) << extra_output << "\t" << time << "\n";
    return time;
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
void TestSolver(const vector<vector<wchar_t>>& table,
                Solver<HeadNode, OtherNode> s,
                bool need_result = false, bool need_stop = false)
{
    clock_t program_started = clock();
    s.set_table(table);
    clock_t solving_started = clock();
    s.solve();
    auto result = s.get_solution();
    clock_t end = clock();
    double preparing_time = print_time(program_started, solving_started, "Trie creation time:");
    double solving_time = print_time(solving_started, end, "Solving time");
    print_time(program_started, end, "Full time");

    if (need_result)
        print_arr(result, result.size());

    if (need_stop)
    {
        wchar_t c;
        std::wcin >> c; // for pause and memory measurement
    }
}

const int MIN_WORD_LENGTH = 6;
template<typename HeadNode, typename OtherNode = HeadNode>
Solver<HeadNode, OtherNode> get_solver(vector<wstring> dict, int min_length = MIN_WORD_LENGTH)
{
    return Solver<HeadNode, OtherNode>(min_length, dict);
};

template<typename HeadNode, typename OtherNode = HeadNode>
Solver<HeadNode, OtherNode> get_solver(string dict_path, int min_length = MIN_WORD_LENGTH)
{
    return Solver<HeadNode, OtherNode>(min_length, dict_path);
};

int main(int argc, char** args)
{
    wcout.imbue(ulocale);


    string dictFile("../Dictionaries/dict.txt");
    string tableFile("../Tables/table2x50.txt");

    const std::string shortened_dict_path = "../Dictionaries/shortened_dict.txt";
    if (argc == 3) // if the arguments specify the full_dict and table files
    {
        dictFile = args[1];
        tableFile = args[2];
    }

    // Measure the reading from file system.
    clock_t reading_start = clock();
    auto full_dict = read_dict(dictFile);
    auto table = read_table(tableFile);
    clock_t reading_end = clock();
    std::wcout << std::setw(20) << "Reading time: \t" << sec(reading_start, reading_end) << "\n";


//    wcout << "Array node: " << endl;
//    TestSolver<ArrayNode>(table, full_dict);
//
//    wcout << "Array node: " << endl;
//    TestSolver2<ArrayNode>(table, shortened_dict_path);
//
//    wcout << "\n\nList node: " << endl;
//    TestSolver<ListNode>(table, full_dict);
//
//    wcout << "List node: " << endl;
//    TestSolver2<ListNode>(table, shortened_dict_path);
//
//    wcout << "\n\nHash node: " << endl;
//    TestSolver<HashNode>(table, full_dict);
//
//    wcout << "Hash node: " << endl;
//    TestSolver2<HashNode>(table, shortened_dict_path);

    wcout << "\n\nMix nodes: " << endl;
    TestSolver(table, get_solver<ArrayNode, ListNode>(full_dict));

    wcout << "Mix nodes: " << endl;
    TestSolver(table, get_solver<ArrayNode, ListNode>(shortened_dict_path), true);

    return 0;
}