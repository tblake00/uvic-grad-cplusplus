#include "TextFormatting.h"
#include "Alphabet.h"

#include <vector> 
#include <map> 
#include <string> 
#include <regex> 

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

std::string regexReplaceNumber( const std::string& inputString ){ 

    static const std::vector< std::string > numberList = { 
            "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" 
    };

    std::string result{""};
    std::regex  replacementPattern{"\\d"}; 
    std::smatch replacementMatch;  

    auto stringPos = inputString.cbegin();
    auto stringEnd = inputString.cend();

    while ( std::regex_search( stringPos, stringEnd, replacementMatch, replacementPattern ) ){
        result += replacementMatch.prefix();
        result += numberList[ replacementMatch.str()[0] - '0' ];
        stringPos += ( replacementMatch.position() + replacementMatch.length() );
    }

    result += replacementMatch.suffix();

    return result;
}

std::string formatInputString( const std::string& inputString ){ 

    std::string processedString{""};

    for ( auto inputChar: inputString ){ 
        if ( std::isalpha( inputChar ) ){
            processedString += std::toupper( inputChar );
        }
        else if ( std::isdigit( inputChar ) ){
            processedString += numberToWord( inputChar );
        }
    }

    return processedString;
}