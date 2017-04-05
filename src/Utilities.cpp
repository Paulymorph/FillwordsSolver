//
// Created by Paul Danilin on 05/04/2017.
//
#include <stdexcept>
#include <iostream>

int hash(wchar_t c, int modulus)
{
    if (c == L'Ё')
        c = L'Е';

    if (c == L'ё')
        c = L'е';

    wchar_t result = (c - L'А') % modulus;

    // Correctness check
    if (result < 0)
    {
        std::wcout << c << std::endl;
        throw std::logic_error("Made the hash crazy!");
    }

    return result;
}