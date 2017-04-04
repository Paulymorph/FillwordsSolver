#include <iostream>
#include "Trie.hpp"
#include "ArrayNode.h"

void Test()
{
    Trie<ArrayNode> t({"asdf", "dfhj"});
    std::cout << t.is_in_leaf() << std::endl;
    std::cout << t.move_along('a') << std::endl;
    std::cout << t.move_along('s') << std::endl;
    std::cout << t.move_along('d') << std::endl;
    std::cout << t.move_along('f') << std::endl;
    std::cout << t.is_in_leaf() << std::endl;
    std::cout << t.move_along('f') << std::endl;
}

int main()
{
    Test();
    char c;
    std::cin >> c;
    return 0;
}