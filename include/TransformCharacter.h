#ifndef TRANSFORMCHARACTER_H
#define TRANSFORMCHARACTER_H

#include <string> 
#include <string_view> 

namespace AlphabetTransform { 
    constexpr std::string_view alphabetLetters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    constexpr std::size_t alphabetLength{ alphabetLetters.size() }; 

    char shiftPosition( const char inputChar, const size_t offsetChar, const int processMode );  
    char shiftCharacter( const char inputChar, const char offsetChar , const int processMode );
}

namespace CharacterTransform { 
    char shiftPosition( const char inputChar, const size_t offsetChar, const int processMode ); 
    char shiftCharacter( const char inputChar, const char offsetChar , const int processMode );
}

#endif 