#include "TextFormatting.h"

#include <vector> 
#include <map> 
#include <string> 

std::string numberToWordUsingCase( const char inputChar ){ 
    
    switch ( inputChar ){ 
        case '0': 
            return "ZERO";
        case '1': 
            return "ONE";
        case '2':
            return "TWO";
        case '3': 
            return "THREE"; 
        case '4':
            return "FOUR"; 
        case '5': 
            return "FIVE"; 
        case '6': 
            return "SIX"; 
        case '7': 
            return "SEVEN"; 
        case '8': 
            return "EIGHT";
        case '9': 
            return "NINE"; 
    }
    return ""; 
}

std::string numberToWordUsingMap( const char inputChar ){ 
    
    // Define map between characters and strings
    static const std::map< const char, const std::string > numberMap = { 
            { '0', "ZERO" },
            { '1', "ONE" }, 
            { '2', "TWO" }, 
            { '3', "THREE" },
            { '4', "FOUR" },
            { '5', "FIVE" },
            { '6', "SIX" },
            { '7', "SEVEN" }, 
            { '8', "EIGHT" },
            { '9', "NINE" }
    };
    
    // Check if the character is in the map
    auto it = numberMap.find( inputChar );

    // Conditional return based on whether the character is found
    return ( it == numberMap.end() ? "" : it->second ); 
}

std::string numberToWord( const char inputChar ){ 
    if ( std::isdigit( inputChar ) ){
        static const std::vector< std::string > numberList = { 
            "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" 
        };

        return numberList[ static_cast< size_t >( inputChar - '0' ) ];
    }
    return ""; 
}
