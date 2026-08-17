#ifndef ALPHABET_H
#define ALPHABET_H

#include <string> 
#include <string_view> 

namespace Alphabet { 
    constexpr std::string_view letters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    constexpr std::size_t length{ letters.size() }; 
}

#endif 